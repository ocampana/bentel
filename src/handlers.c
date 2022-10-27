/*
 * Copyright (c) 2022 Geoff Simmons <geoff@simmons.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 * See LICENSE
 */

#include "pico/cyw43_arch.h"

#include "picow_http/http.h"

#include "handlers.h"

#define MAX_INT_LEN (STRLEN_LTRL("−2147483648"))

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
	if ((err = http_resp_set_type_ltrl(resp, "text/plain")) != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_type_ltrl() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_hdr_ltrl(resp, "Cache-Control", "no-store"))
	    != ERR_OK) {
		HTTP_LOG_ERROR("Set header Cache-Control failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	return http_resp_send_buf(http, body, body_len, false);
}

static const char *bit_str[] = { "0", "1" };

#define ON_LEN (STRLEN_LTRL("on"))
#define OFF_LEN (STRLEN_LTRL("off"))
#define TOGGLE_LEN (STRLEN_LTRL("toggle"))

err_t
led_handler(struct http *http, void *p)
{
	struct req *req = http_req(http);
	struct resp *resp = http_resp(http);
	err_t err;
	bool led_on;
	const char *query;
	size_t query_len;
	int idx;
	(void)p;

	query = http_req_query(req, &query_len);
	led_on = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);

	if (query != NULL) {
		const char *val;
		size_t val_len;

		val = http_req_query_val(query, query_len, "op", 2, &val_len);
		if (val == NULL)
			return http_resp_err(http,
					     HTTP_STATUS_UNPROCESSABLE_CONTENT);

		switch (val_len) {
		case ON_LEN:
			if (memcmp(val, "on", ON_LEN) != 0)
				return http_resp_err(http,
					     HTTP_STATUS_UNPROCESSABLE_CONTENT);
			if (!led_on) {
				cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN,
						    true);
				led_on = true;
			}
			break;
		case OFF_LEN:
			if (memcmp(val, "off", OFF_LEN) != 0)
				return http_resp_err(http,
					     HTTP_STATUS_UNPROCESSABLE_CONTENT);
			if (led_on) {
				cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN,
						    false);
				led_on = false;
			}
			break;
		case TOGGLE_LEN:
			if (memcmp(val, "toggle", TOGGLE_LEN) != 0)
				return http_resp_err(http,
					     HTTP_STATUS_UNPROCESSABLE_CONTENT);
			led_on = !led_on;
			cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
			break;
		default:
			return http_resp_err(http,
					     HTTP_STATUS_UNPROCESSABLE_CONTENT);
		}
	}

	idx = bool_to_bit(led_on);
	if ((err = http_resp_set_len(resp, 1)) != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_len() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_type_ltrl(resp, "text/plain")) != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_type_ltrl() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_hdr_ltrl(resp, "Cache-Control", "no-store"))
	    != ERR_OK) {
		HTTP_LOG_ERROR("Set header Cache-Control failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	return http_resp_send_buf(http, bit_str[idx], 1, true);
}

static const char *bool_str[] = { "false", "true" };

#define RSSI_FMT ("{\"valid\":%s,\"rssi\":%d}")
#define RSSI_MAX ("{\"valid\":false,\"rssi\":-32768}")
#define RSSI_MAX_LEN (STRLEN_LTRL(RSSI_MAX))

err_t
rssi_handler(struct http *http, void *p)
{
	struct resp *resp = http_resp(http);
	err_t err;
	int16_t rssi;
	int idx;
	char body[RSSI_MAX_LEN];
	size_t body_len;
	(void)p;

	rssi = get_rssi();
	idx = bool_to_bit(rssi != INT16_MAX);
	body_len = snprintf(body, RSSI_MAX_LEN, RSSI_FMT, bool_str[idx], rssi);
	if ((err = http_resp_set_len(resp, body_len)) != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_len() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_type_ltrl(resp, "application/json"))
	    != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_type_ltrl() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_hdr_ltrl(resp, "Cache-Control", "no-store"))
	    != ERR_OK) {
		HTTP_LOG_ERROR("Set header Cache-Control failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	return http_resp_send_buf(http, body, body_len, false);
}

#define INFO_FMT \
	("{\"ssid\":\"" WIFI_SSID "\",\"host\":\"" CYW43_HOST_NAME "\"," \
	 "\"ip\":\"%s\",\"mac\":\"%s\"}")
#define INFO_STR \
	("{\"ssid\":\"" WIFI_SSID "\",\"host\":\"" CYW43_HOST_NAME "\"," \
	 "\"ip\":\"\",\"mac\":\"\"}")
#define INFO_MAX_LEN (STRLEN_LTRL(INFO_STR) + IPADDR_STRLEN_MAX + MAC_ADDR_LEN)

#define ETAG_LEN (sizeof("\"12345678\""))

static inline uint32_t
update_hash(const char *p, uint32_t h)
{
	for (; *p != '\0'; p++)
		h = 31 * h + *p;
	return h;
}

static void
set_etag(char etag[], struct netinfo *info)
{
	uint32_t hash = 0;

	hash = update_hash(info->ip, hash);
	hash = update_hash(info->mac, hash);
	hash = update_hash(WIFI_SSID, hash);
	hash = update_hash(CYW43_HOST_NAME, hash);
	snprintf(etag, ETAG_LEN, "\"%08x\"", hash);
}

err_t
netinfo_handler(struct http *http, void *p)
{
	struct req *req = http_req(http);
	struct resp *resp = http_resp(http);
	struct netinfo *info;
	static char etag[ETAG_LEN] = { '\0' };
	char body[INFO_MAX_LEN];
	size_t body_len;
	err_t err;

	CAST_OBJ_NOTNULL(info, p, NETINFO_MAGIC);

	if (etag[0] == '\0')
		set_etag(etag, info);
	if ((err = http_resp_set_hdr(resp, "ETag", STRLEN_LTRL("ETag"), etag,
				     ETAG_LEN - 1)) != ERR_OK) {
		HTTP_LOG_ERROR("Set header ETag failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_hdr_ltrl(resp, "Cache-Control",
					  "public, max-age=3600")) != ERR_OK) {
		HTTP_LOG_ERROR("Set header Cache-Control failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}

	if (http_req_hdr_eq(req, "If-None-Match", STRLEN_LTRL("If-None-Match"),
			    etag, ETAG_LEN - 1)) {
		err = http_resp_set_status(resp, HTTP_STATUS_NOT_MODIFIED);
		if (err != ERR_OK) {
			HTTP_LOG_ERROR("Set status 304 failed: %d", err);
			return http_resp_err(http,
					     HTTP_STATUS_INTERNAL_SERVER_ERROR);
		}
		return http_resp_send_hdr(http);
	}

	body_len = snprintf(body, INFO_MAX_LEN, INFO_FMT, info->ip, info->mac);
	if ((err = http_resp_set_len(resp, body_len)) != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_len() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	if ((err = http_resp_set_type_ltrl(resp, "application/json"))
	    != ERR_OK) {
		HTTP_LOG_ERROR("http_resp_set_type_ltrl() failed: %d", err);
		return http_resp_err(http, HTTP_STATUS_INTERNAL_SERVER_ERROR);
	}
	return http_resp_send_buf(http, body, body_len, false);
}
