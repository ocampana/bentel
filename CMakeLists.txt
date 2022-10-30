cmake_minimum_required(VERSION 3.12)

# From pico-sdk, to integrate the SDK into the project.
include(pico_sdk_import.cmake)

# Creates targets for use with a picoprobe, to flash the code and
# reset the app. This requires that the locations of openocd and
# optionally of its search path are in environment variables, or
# passed to cmake as -D definitions. See the included file for
# details.
include(picoprobe_targets.cmake)

project(picow-http-example C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# picow-http is included in this project as a git submodule, so it can
# be integrated with add_subdirectory().
#
# If instead you have picow-http installed elsewhere on your system,
# use include():
#
# include(path/to/picow-http)
#
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/lib/picow-http)

# For use with a picoprobe (this has nothing to do with picow-http).
# 'make reset' restarts the app.
picoprobe_add_reset_target()

# If NTP_SERVER is defined in the cmake invocation, pass in its value
# to the preprocessor. See main.c
if (DEFINED NTP_SERVER)
	add_compile_definitions(NTP_SERVER=\"${NTP_SERVER}\")
endif()

# Optionally override the PicoW default hostname.
if (DEFINED HOSTNAME)
	add_compile_definitions(CYW43_HOST_NAME=\"${HOSTNAME}\")
endif()

# This project has targets for more than one executable, which differ
# only in the choice of network architecture; see the SDK docs for
# pico_cyw43_arch. Most apps will choose just one, but the example
# includes more for demonstration purposes.
#
# The following definitions summarize elements that the different
# excutables have in common.

# Source files
# We use the sample lwipopts.h definition from picow-http.
# See: https://gitlab.com/slimhazard/picow_http/-/wikis/Configuring-lwipopts.h
set(SRCS
	${CMAKE_CURRENT_LIST_DIR}/src/main.c
	${CMAKE_CURRENT_LIST_DIR}/src/handlers.c
	${CMAKE_CURRENT_LIST_DIR}/src/handlers.h
	${CMAKE_CURRENT_LIST_DIR}/lib/picow-http/etc/lwipopts.h
)

# Include paths
# Must include the path at which lwipopts.h is located.
set(INCLUDES
	${CMAKE_CURRENT_LIST_DIR}/src
	${CMAKE_CURRENT_LIST_DIR}/lib/picow-http/etc
)

# Static WWW resources to be embedded for the HTTP server.
set(WWWSRCS
	${CMAKE_CURRENT_LIST_DIR}/www/index.html
	${CMAKE_CURRENT_LIST_DIR}/www/picow.css
	${CMAKE_CURRENT_LIST_DIR}/www/img/favicon.png
	${CMAKE_CURRENT_LIST_DIR}/www/sample_app.js
)

# Libraries to be linked
# The different versions link different choices for pico_cyw43_arch_lwip_*,
# otherwise the libs are the same.
set(LIBS
	picow_http
	pico_stdio
	pico_stdlib
	pico_multicore
	hardware_adc
	hardware_irq
	hardware_sync
)

# The next sections configure the executables; mostly standard for the
# SDK. The picow_http_gen_handlers() directive is required for use
# with picow-http.

##
## threadsafe background mode
##

add_executable(picow-http-example-background ${SRCS})

target_compile_definitions(picow-http-example-background PRIVATE
	WIFI_SSID=\"${WIFI_SSID}\"
	WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
)

target_include_directories(picow-http-example-background PRIVATE ${INCLUDES})

# pico_cyw43_arch_lwip_threadsafe_background sets the network
# architecture.
target_link_libraries(picow-http-example-background
	pico_cyw43_arch_lwip_threadsafe_background
	${LIBS}
)

# The arguments for picow_http_gen_handlers() are:
# - target name
# - YAML file that configures static resources and custom response
#   handlers
# - Directory that contains the static resources
# - List of static resources; here defined in WWWSRCS above.
# See: https://gitlab.com/slimhazard/picow_http/-/wikis/picow_http_gen_handlers
picow_http_gen_handlers(picow-http-example-background
	${CMAKE_CURRENT_SOURCE_DIR}/www/www.yaml
	${CMAKE_CURRENT_SOURCE_DIR}/www
	${WWWSRCS}
)

# This defines UART, but not USB, as the destination for the HTTP
# server's log output.
pico_enable_stdio_usb(picow-http-example-background 0)
pico_enable_stdio_uart(picow-http-example-background 1)

pico_add_extra_outputs(picow-http-example-background)

# For use with a picoprobe.
# 'make flash-picow-http-example-background' loads the binary to the
# PicoW.
picoprobe_add_flash_target(picow-http-example-background)

pico_set_program_description(picow-http-example-background
	"example app for the picow-http library, threadsafe background mode"
)
pico_set_program_url(picow-http-example-background
	"https://gitlab.com/slimhazard/picow-http-example"
)

##
## poll mode
##

add_executable(picow-http-example-poll ${SRCS})

target_compile_definitions(picow-http-example-poll PRIVATE
	WIFI_SSID=\"${WIFI_SSID}\"
	WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
)

target_include_directories(picow-http-example-poll PRIVATE ${INCLUDES})

# pico_cyw43_arch_lwip_poll sets the network architecture tp poll
# mode.
target_link_libraries(picow-http-example-poll
	pico_cyw43_arch_lwip_poll
	${LIBS}
)

# Exactly as above
picow_http_gen_handlers(picow-http-example-poll
 	${CMAKE_CURRENT_SOURCE_DIR}/www/www.yaml
 	${CMAKE_CURRENT_SOURCE_DIR}/www
 	${WWWSRCS}
)

pico_enable_stdio_usb(picow-http-example-poll 0)
pico_enable_stdio_uart(picow-http-example-poll 1)

pico_add_extra_outputs(picow-http-example-poll)

picoprobe_add_flash_target(picow-http-example-poll)

pico_set_program_description(picow-http-example-poll
	"example app for the picow-http library, poll mode"
)
pico_set_program_url(picow-http-example-poll
	"https://gitlab.com/slimhazard/picow-http-example"
)

##
## Use the output of 'git describe', if available, as the version
## string
##
set(PROGRAM_VERSION "unknown")
find_program(GIT git)
if (NOT GIT_FOUND)
	execute_process(COMMAND ${GIT} describe --always
		OUTPUT_VARIABLE GIT_DESCRIBE_OUTPUT
		OUTPUT_STRIP_TRAILING_WHITESPACE
		RESULT_VARIABLE GIT_DESCRIBE_RESULT
	)
	if (GIT_DESCRIBE_RESULT EQUAL "0")
		set(PROGRAM_VERSION ${GIT_DESCRIBE_OUTPUT})
	else()
		message(WARNING "git describe returned ${GIT_DESCRIBE_RESULT}")
	endif()
else()
	message(WARNING "git not found")
endif()
message("version: ${PROGRAM_VERSION}")

target_compile_definitions(picow-http-example-background PRIVATE
	PROGRAM_VERSION="${PROGRAM_VERSION}"
)
target_compile_definitions(picow-http-example-poll PRIVATE
	PROGRAM_VERSION="${PROGRAM_VERSION}"
)
pico_set_program_version(picow-http-example-background ${PROGRAM_VERSION})
pico_set_program_version(picow-http-example-poll ${PROGRAM_VERSION})
