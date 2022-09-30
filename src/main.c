/*
 * Copyright (c) 2022 Geoff Simmons <geoff@simmons.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 * See LICENSE
 */

#include <stdio.h>
#include <stdint.h>

#include "pico/stdio_uart.h"
#include "pico/cyw43_arch.h"
#include "pico/multicore.h"
#include "pico/sync.h"
#include "hardware/adc.h"
#include "hardware/regs/adc.h"
#include "hardware/sync.h"

#include "picow_http/http.h"
#include "handlers.h"

#define ADC_TEMP_CH (4)
/*
 * Maximum value for the ADC clock divider. Results in about 732,4 Hz, or
 * approximately one measurement every 1 1/3 ms.
 */
#define ADC_MAX_CLKDIV (65535.f + 255.f/256.f)

#define AP_SCAN_INTVL_MS (10 * 1000)

static volatile uint16_t temp_adc_raw = UINT16_MAX;
static volatile bool linkup = false;
static volatile int16_t rssi = INT16_MAX;
static critical_section_t temp_critsec, rssi_critsec, linkup_critsec;
static repeating_timer_t scan_timer;

static void
__not_in_flash_func(temp_isr)(void)
{
	uint16_t val = adc_fifo_get();
	critical_section_enter_blocking(&temp_critsec);
	temp_adc_raw = val;
	critical_section_exit(&temp_critsec);
}

uint32_t
get_temp(void)
{
	uint16_t raw;

	critical_section_enter_blocking(&temp_critsec);
	raw = temp_adc_raw;
	critical_section_exit(&temp_critsec);

	if (raw == UINT16_MAX)
		return UINT32_MAX;
	if ((raw & ADC_FIFO_ERR_BITS) != 0)
		return UINT32_MAX;
	return 2909703 - 1917 * raw;
}

int16_t
get_rssi(void)
{
	int16_t val;

	critical_section_enter_blocking(&rssi_critsec);
	val = rssi;
	critical_section_exit(&rssi_critsec);
	return val;
}

static int
scan_result(void *p, const cyw43_ev_scan_result_t *result)
{
	const char *ssid = p;

	AN(ssid);
	AN(result);
	AN(result->ssid);
	if (strncmp(ssid, result->ssid, result->ssid_len) != 0)
		return 0;
	critical_section_enter_blocking(&rssi_critsec);
	rssi = result->rssi;
	critical_section_exit(&rssi_critsec);
	return 0;
}

static bool
scan_start(repeating_timer_t *rt)
{
	cyw43_wifi_scan_options_t opts = { 0 };

	AN(rt);
	if (cyw43_wifi_scan_active(&cyw43_state))
		return true;
	if (cyw43_wifi_scan(&cyw43_state, &opts, rt->user_data, scan_result)
	    != 0)
		HTTP_LOG_ERROR("cyw43_wifi_scan() failed");
	return true;
}

void
core1_main(void)
{
	/* Initiate asynchronous ADC temperature sensor reads */
	adc_init();
	adc_set_temp_sensor_enabled(true);
	adc_select_input(ADC_TEMP_CH);
	/* Write to FIFO length 1, and retain the ERR bit. */
	adc_fifo_setup(true, false, 1, true, false);
	adc_set_clkdiv(ADC_MAX_CLKDIV);

	irq_set_exclusive_handler(ADC_IRQ_FIFO, temp_isr);
	adc_irq_set_enabled(true);
	irq_set_enabled(ADC_IRQ_FIFO, true);
	adc_run(true);

	/* Wait for the other core to signal that the network link is up. */
	for (;;) {
		bool up = false;

		critical_section_enter_blocking(&linkup_critsec);
		up = linkup;
		critical_section_exit(&linkup_critsec);
		if (up)
			break;
		sleep_ms(100);
	}

	if (!add_repeating_timer_ms(AP_SCAN_INTVL_MS, scan_start, WIFI_SSID,
				    &scan_timer))
		HTTP_LOG_ERROR("Failed to start timer for AP scan");

	for (;;)
		__wfi();
}

int
main(void)
{
	struct server *srv;
	struct server_cfg cfg;
	struct ntp_cfg ntp_cfg;
	int link_status = CYW43_LINK_DOWN;
	err_t err;

	critical_section_init(&temp_critsec);
	critical_section_init(&linkup_critsec);
	critical_section_init(&rssi_critsec);
	sleep_ms(10);
	multicore_reset_core1();
	sleep_ms(10);
	multicore_launch_core1(core1_main);

	stdout_uart_init();

	if (cyw43_arch_init() != 0)
		return -1;

	cyw43_arch_enable_sta_mode();
	HTTP_LOG_INFO("Connecting to " WIFI_SSID " ...");
	do {
		if (cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD,
						  CYW43_AUTH_WPA2_AES_PSK) != 0)
			continue;
		while ((link_status = cyw43_tcpip_link_status(&cyw43_state,
							      CYW43_ITF_STA))
		       != CYW43_LINK_UP) {
			if (link_status < 0) {
				HTTP_LOG_ERROR("WiFi connect error status: %d",
					       link_status);
				break;
			}
			sleep_ms(100);
		}
	} while (link_status != CYW43_LINK_UP);

	critical_section_enter_blocking(&linkup_critsec);
	linkup = true;
	critical_section_exit(&linkup_critsec);
	HTTP_LOG_INFO("Connected to " WIFI_SSID);

	if ((err = register_hndlr("/temp", temp_handler, HTTP_METHOD_GET, NULL))
	    != ERR_OK) {
		HTTP_LOG_ERROR("register_hndlr GET /temp: %d", err);
		return -1;
	}
	if ((err = register_hndlr("/temp", temp_handler, HTTP_METHOD_HEAD,
				  NULL)) != ERR_OK) {
		HTTP_LOG_ERROR("register_hndlr HEAD /temp: %d", err);
		return -1;
	}
	if ((err = register_hndlr("/led", led_handler, HTTP_METHOD_GET, NULL))
	    != ERR_OK) {
		HTTP_LOG_ERROR("register_hndlr GET /led: %d", err);
		return -1;
	}
	if ((err = register_hndlr("/led", led_handler, HTTP_METHOD_HEAD, NULL))
	    != ERR_OK) {
		HTTP_LOG_ERROR("register_hndlr HEAD /led: %d", err);
		return -1;
	}
	if ((err = register_hndlr("/ap", ap_handler, HTTP_METHOD_GET, NULL))
	    != ERR_OK) {
		HTTP_LOG_ERROR("register_hndlr GET /ap: %d", err);
		return -1;
	}
	if ((err = register_hndlr("/ap", led_handler, HTTP_METHOD_HEAD, NULL))
	    != ERR_OK) {
		HTTP_LOG_ERROR("register_hndlr HEAD /ap: %d", err);
		return -1;
	}

	http_default_cfg(&cfg, &ntp_cfg);
#ifdef NTP_SERVER
	ntp_cfg.server = NTP_SERVER;
#endif
	while ((err = http_srv_init(&srv, &cfg)) != ERR_OK)
		HTTP_LOG_ERROR("http_init: %d\n", err);
	HTTP_LOG_INFO("http started");
	cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);

	for (;;)
		__wfi();

	cyw43_arch_deinit();
	return 0;
}
