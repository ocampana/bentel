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

//#include "picow_http/http.h"

#define ADC_TEMP_CH (4)
/* Clock divider to run the ADC at 0.5 Hz (48 MHz clock) */
#define ADC_0_5_HZ (24 * 1000 * 1000)

static volatile uint16_t temp_adc_raw;
static critical_section_t temp_critsec;

static void
__not_in_flash_func(temp_isr)(void)
{
	uint16_t val = adc_fifo_get();
	critical_section_enter_blocking(&temp_critsec);
	temp_adc_raw = val;
	critical_section_exit(&temp_critsec);
}

static uint32_t
get_temp(void)
{
	uint16_t raw;

	critical_section_enter_blocking(&temp_critsec);
	raw = temp_adc_raw;
	critical_section_exit(&temp_critsec);

	if ((raw & ADC_FIFO_ERR_BITS) != 0)
		return 0;
	return 2909703 - 1917 * raw;
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
	adc_set_clkdiv(ADC_0_5_HZ);

	irq_set_exclusive_handler(ADC_IRQ_FIFO, temp_isr);
	adc_irq_set_enabled(true);
	irq_set_enabled(ADC_IRQ_FIFO, true);
	adc_run(true);

	for (;;)
		__wfi();
}

int
main(void)
{
#if 0
	struct server *srv;
	struct server_cfg cfg;
	struct ntp_cfg ntp_cfg;
#endif
	int link_status = CYW43_LINK_DOWN;
	err_t err;

	critical_section_init(&temp_critsec);
	sleep_ms(10);
	multicore_reset_core1();
	sleep_ms(10);
	multicore_launch_core1(core1_main);

	stdout_uart_init();

	if (cyw43_arch_init() != 0)
		return -1;

#if 0
	cyw43_arch_enable_sta_mode();
	do {
		if (cyw43_arch_wifi_connect_async(WIFI_SSID, WIFI_PASSWORD,
						  CYW43_AUTH_WPA2_AES_PSK) != 0)
			continue;
		while ((link_status = cyw43_tcpip_link_status(&cyw43_state,
							      CYW43_ITF_STA))
		       != CYW43_LINK_UP) {
			if (link_status < 0)
				break;
			sleep_ms(100);
		}
	} while (link_status != CYW43_LINK_UP);

	if ((err = register_hndlr("/reflect", reflect_hndlr, HTTP_METHOD_GET,
				  NULL)) != ERR_OK) {
		printf("register_hndlr GET: %d\n", err);
		return -1;
	}

	http_default_cfg(&cfg, &ntp_cfg);
#endif
#ifdef NTP_SERVER
	ntp_cfg.server = NTP_SERVER;
#endif
#if 0
	while ((err = http_srv_init(&srv, &cfg)) != ERR_OK)
		printf("http_init: %d\n", err);
	puts("http started");
#endif

	for (;;) {
		uint32_t temp = get_temp();

		if (temp != 0)
			// HTTP_LOG_INFO("Temp K (Q20.12) = %u", temp);
			printf("Temp K (Q20.12) = %u\n", temp);
		else
			// HTTP_LOG_ERROR("ADC error");
			puts("ADC error");
		sleep_ms(1000);
	}
#if 0
	for (;;)
		__wfi();
#endif

	cyw43_arch_deinit();
	return 0;
}
