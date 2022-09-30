cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
include(picoprobe_targets.cmake)

project(picow_http C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/picow-http)

picoprobe_add_reset_target()

add_executable(picow-http-example
	${CMAKE_CURRENT_LIST_DIR}/src/main.c
	${CMAKE_CURRENT_LIST_DIR}/src/handlers.c
	${CMAKE_CURRENT_LIST_DIR}/src/handlers.h
	${CMAKE_CURRENT_LIST_DIR}/src/lwipopts.h
)

target_compile_definitions(picow-http-example PRIVATE
	WIFI_SSID=\"${WIFI_SSID}\"
	WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
)

if (DEFINED NTP_SERVER)
	add_compile_definitions(NTP_SERVER=\"${NTP_SERVER}\")
endif()

if (DEFINED HOSTNAME)
	add_compile_definitions(CYW43_HOST_NAME=\"${HOSTNAME}\")
endif()

target_include_directories(picow-http-example PRIVATE
	${CMAKE_CURRENT_LIST_DIR}/src
)

target_link_libraries(picow-http-example
	picow_http
	pico_cyw43_arch_lwip_threadsafe_background
	pico_stdio
	pico_stdlib
	pico_multicore
	hardware_adc
	hardware_irq
	hardware_sync
)

set(WWWSRCS
 	${CMAKE_CURRENT_LIST_DIR}/www/index.html
 	${CMAKE_CURRENT_LIST_DIR}/www/picow.css
 	${CMAKE_CURRENT_LIST_DIR}/www/favicon.png
 	${CMAKE_CURRENT_LIST_DIR}/www/sample_app.js
)

picow_http_gen_handlers(picow-http-example
 	${CMAKE_CURRENT_SOURCE_DIR}/www/www.yaml
 	${CMAKE_CURRENT_SOURCE_DIR}/www
 	${WWWSRCS}
)

pico_enable_stdio_usb(picow-http-example 0)
pico_enable_stdio_uart(picow-http-example 1)

pico_add_extra_outputs(picow-http-example)

picoprobe_add_flash_target(picow-http-example)
