/*
 * Copyright (c) 2022 Geoff Simmons <geoff@simmons.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 * See LICENSE
 */

#include <stdint.h>

#include "lwip/ip_addr.h"
#include "picow_http/http.h"

#define MAC_ADDR_LEN (sizeof("01:02:03:04:05:06"))

struct netinfo {
	unsigned	magic;
#define NETINFO_MAGIC (0x4f5dde9f)
	char		ip[IPADDR_STRLEN_MAX];
	char		mac[MAC_ADDR_LEN];
};

uint32_t get_temp(void);
int16_t get_rssi(void);

err_t temp_handler(struct http *http, void *p);
err_t led_handler(struct http *http, void *p);
err_t rssi_handler(struct http *http, void *p);
err_t netinfo_handler(struct http *http, void *p);
