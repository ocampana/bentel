cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
include(picoprobe_targets.cmake)

project(picow_http C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/picow-http)

picoprobe_add_reset_target()

if (DEFINED NTP_SERVER)
	add_compile_definitions(NTP_SERVER=\"${NTP_SERVER}\")
endif()

if (DEFINED HOSTNAME)
	add_compile_definitions(CYW43_HOST_NAME=\"${HOSTNAME}\")
endif()

set(SRCS
	${CMAKE_CURRENT_LIST_DIR}/src/main.c
	${CMAKE_CURRENT_LIST_DIR}/src/handlers.c
	${CMAKE_CURRENT_LIST_DIR}/src/handlers.h
	${CMAKE_CURRENT_LIST_DIR}/lib/picow-http/etc/lwipopts.h
)

set(INCLUDES
	${CMAKE_CURRENT_LIST_DIR}/src
	${CMAKE_CURRENT_LIST_DIR}/lib/picow-http/etc
)

set(WWWSRCS
	${CMAKE_CURRENT_LIST_DIR}/www/index.html
	${CMAKE_CURRENT_LIST_DIR}/www/picow.css
	${CMAKE_CURRENT_LIST_DIR}/www/img/favicon.png
	${CMAKE_CURRENT_LIST_DIR}/www/sample_app.js
)

##
## threadsafe background mode
##

add_executable(picow-http-example-background ${SRCS})

target_compile_definitions(picow-http-example-background PRIVATE
	WIFI_SSID=\"${WIFI_SSID}\"
	WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
)

target_include_directories(picow-http-example-background PRIVATE ${INCLUDES})

target_link_libraries(picow-http-example-background
	picow_http
	pico_cyw43_arch_lwip_threadsafe_background
	pico_stdio
	pico_stdlib
	pico_multicore
	hardware_adc
	hardware_irq
	hardware_sync
)

picow_http_gen_handlers(picow-http-example-background
	${CMAKE_CURRENT_SOURCE_DIR}/www/www.yaml
	${CMAKE_CURRENT_SOURCE_DIR}/www
	${WWWSRCS}
)

pico_enable_stdio_usb(picow-http-example-background 0)
pico_enable_stdio_uart(picow-http-example-background 1)

pico_add_extra_outputs(picow-http-example-background)

picoprobe_add_flash_target(picow-http-example-background)

##
## poll mode
##

add_executable(picow-http-example-poll ${SRCS})

target_compile_definitions(picow-http-example-poll PRIVATE
	WIFI_SSID=\"${WIFI_SSID}\"
	WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
)

target_include_directories(picow-http-example-poll PRIVATE ${INCLUDES})

target_link_libraries(picow-http-example-poll
	picow_http
	pico_cyw43_arch_lwip_poll
	pico_stdio
	pico_stdlib
	pico_multicore
	hardware_adc
	hardware_irq
	hardware_sync
)

picow_http_gen_handlers(picow-http-example-poll
 	${CMAKE_CURRENT_SOURCE_DIR}/www/www.yaml
 	${CMAKE_CURRENT_SOURCE_DIR}/www
 	${WWWSRCS}
)

pico_enable_stdio_usb(picow-http-example-poll 0)
pico_enable_stdio_uart(picow-http-example-poll 1)

pico_add_extra_outputs(picow-http-example-poll)

picoprobe_add_flash_target(picow-http-example-poll)
