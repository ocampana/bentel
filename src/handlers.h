/*
 * Copyright (c) 2022 Geoff Simmons <geoff@simmons.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 * See LICENSE
 */

#include <stdint.h>

#include "picow_http/http.h"

uint32_t get_temp(void);
int16_t get_rssi(void);

err_t temp_handler(struct http *http, void *p);
err_t led_handler(struct http *http, void *p);
err_t ap_handler(struct http *http, void *p);
