/*
 * Copyright (c) 2022 Geoff Simmons <geoff@simmons.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 * See LICENSE
 */

#include "pico/cyw43_arch.h"

#include "picow_http/http.h"

#include "handlers.h"

#define MAX_INT_LEN (STRLEN_LITERAL("−2147483648"))

err_t
temp_handler(struct http *http, void *p)
{
	struct resp *resp = http_resp(http);
	uint32_t temp;
	err_t err;
	char body[MAX_INT_LEN];
	size_t body_len = MAX_INT_LEN;
	(void)p;

	temp = get_temp();
	if (temp > INT32_MAX) {
		HTTP_LOG_ERROR("get_temp() failed: temp=%d", temp);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = format_decimal(body, &body_len, temp)) != ERR_OK) {
		HTTP_LOG_ERROR("format_decimal() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_len(resp, body_len)) != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_len() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_type_literal(resp, "text/plain")) != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_type_literal() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	return http_resp_send_buf(http, body, body_len, false);
}

static const char *bool_str[] = { "false", "true" };
static const size_t bool_body_len[] = {
	STRLEN_LITERAL("false"),
	STRLEN_LITERAL("true"),
};

#define QUERY_PFX_LEN (STRLEN_LITERAL("op="))
#define ON_LEN (STRLEN_LITERAL("on"))
#define OFF_LEN (STRLEN_LITERAL("off"))
#define TOGGLE_LEN (STRLEN_LITERAL("toggle"))

err_t
led_handler(struct http *http, void *p)
{
	struct req *req = http_req(http);
	struct resp *resp = http_resp(http);
	err_t err;
	bool led_on;
	const char *query;
	size_t query_len, body_len;
	int idx;
	(void)p;

	query = http_req_query(req, &query_len);
	led_on = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);

	if (query != NULL) {
		const char *val;

		if (query_len < QUERY_PFX_LEN
		    || memcmp(query, "op=", QUERY_PFX_LEN) != 0)
			return http_resp_err(http,
					     HTTP_STATUS_UNPROCESSABLE_CONTENT);

		val = query + QUERY_PFX_LEN;
		if (query_len == QUERY_PFX_LEN + ON_LEN
		    && memcmp(val, "on", ON_LEN) == 0) {
			if (!led_on) {
				cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN,
						    true);
				led_on = true;
			}
		}
		else if (query_len == QUERY_PFX_LEN + OFF_LEN
			 && memcmp(val, "off", OFF_LEN) == 0) {
			if (led_on) {
				cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN,
						    false);
				led_on = false;
			}
		}
		else if (query_len == QUERY_PFX_LEN + TOGGLE_LEN
			 && memcmp(val, "toggle", TOGGLE_LEN) == 0) {
			led_on = !led_on;
			cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
		}
		else
			return http_resp_err(http,
					     HTTP_STATUS_UNPROCESSABLE_CONTENT);
	}

	idx = bool_to_bit(led_on);
	body_len = bool_body_len[idx];
	if ((err = http_resp_set_len(resp, body_len)) != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_len() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_type_literal(resp, "text/plain")) != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_type_literal() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	return http_resp_send_buf(http, bool_str[idx], body_len, true);
}

static const char *json_fmt =
	"{ssid:\"" WIFI_SSID "\",have_rssi=\"%s\",rssi:%d}";
#define JSON_MAX_LEN \
    (STRLEN_LITERAL("{ssid:\"" WIFI_SSID "\",have_rssi=\"false\",rssi:-32768}"))

err_t
ap_handler(struct http *http, void *p)
{
	struct resp *resp = http_resp(http);
	err_t err;
	int16_t rssi;
	int idx;
	char body[JSON_MAX_LEN];
	size_t body_len;
	(void)p;

	rssi = get_rssi();
	idx = bool_to_bit(rssi != INT16_MAX);
	body_len = snprintf(body, JSON_MAX_LEN, json_fmt, bool_str[idx], rssi);
	if ((err = http_resp_set_len(resp, body_len)) != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_len() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_type_literal(resp, "application/json"))
	    != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_type_literal() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	return http_resp_send_buf(http, body, body_len, false);
}
