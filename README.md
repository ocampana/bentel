# picow-http-example

picow-http-example is a sample application to demonstrate
[picow-http](https://gitlab.com/slimhazard/picow_http) -- an HTTP server
for the [Raspberry Pi Pico W
microcontroller](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html#raspberry-pi-pico-w-and-pico-wh).

The sample is a single-page application for a web browser that displays:

  * The state of the PicoW's onboard LED (on or off).
    * The user can turn on, turn off, and toggle the LED.
  * Measurements from the PicoW's onboard temperature sensor.
    * The user can choose the temperature scale (Kelvin, Celsius, or
      Fahrenheit).
  * Information about the PicoW's network connection, including the
    signal strength of the access point, displayed in percent and as
    [rssi](https://en.wikipedia.org/wiki/Received_signal_strength_indication)
    in dBm.

While the app is visible in a browser window, the temperature and
signal strength measurements are updated every few seconds.

See the [project
Wiki](https://gitlab.com/slimhazard/picow-http-example/-/wikis/Home) for
[screenshots](https://gitlab.com/slimhazard/picow-http-example/-/wikis/Screenshots)
of the app as seen in various browsers.

These are far from the most interesting things that a PicoW can do;
but the app can be deployed without any additional hardware besides
the PicoW board, or additional software libraries besides picow-http
and the
[SDK](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html).
The example illustrates:

  * Configuring and embedding static resources: HTML, CSS, Javascript
    and a PNG image.
  * Implementing custom response handlers for dynamic content.
  * Basic guidelines for separation of concerns:
    * Presentation logic on the client side (in Javascript)
    * Utilizing the browser cache
    * Separation of the HTTP server from core hardware functions on
      the PicoW

Specifically in the sample app:

  * Static resources in the [`www/`](www/) subdirectory are embedded.
  * Four [custom response handlers](src/handlers.c) are implemented for
    temperature, the LED, rssi, and network information.
  * Static resources and custom handlers are configured in
    [`www.yaml`](www/www.yaml).

For more information about the picow-http server library, see:

  * the [git repository](https://gitlab.com/slimhazard/picow_http)
  * the picow-http [project
    Wiki](https://gitlab.com/slimhazard/picow_http/-/wikis/home)
  * the [public API documentation](https://slimhazard.gitlab.io/picow_http/)

## Build/Install

### Quick start

Ensure that [requirements](#requirements) are fulfilled. Then:

```shell
$ git clone --recurse-submodules https://gitlab.com/slimhazard/picow-http-example.git
$ cd picow-http-example
$ mkdir build
$ cd build
$ cmake -DPICO_BOARD=pico_w -DWIFI_SSID=my_wifi -DWIFI_PASSWORD=wifi_pass ..
$ make -j
```

On successful build, [load one of the binaries](#deploying-the-app) to
your board in any of the usual ways for the PicoW.

Finally point your browser to `http://PicoW`. The [server
log](#monitoring-the-log) can be viewed via UART.

In the following we go over the process step by step.

### Requirements

The [Pico C SDK](https://raspberrypi.github.io/pico-sdk-doxygen/index.html)
and its toolchain are required to build the app. picow-http also requires
some [additional
software](https://gitlab.com/slimhazard/picow_http/-/wikis/required-software);
see the link (at the [picow-http project
Wiki](https://gitlab.com/slimhazard/picow_http/-/wikis/home)) for details.

### Building the app

Start by cloning the repository:

```shell
# Clones the repository into a new directory 'picow-http-example',
# and updates the picow-http submodule.
$ git clone --recurse-submodules https://gitlab.com/slimhazard/picow-http-example.git
```

picow-http is a [git
submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) in the
repo at the path [`lib/picow-http`](lib/picow-http); it is
automatically updated when the `--recurse-submodules` option is used
with the `git clone` command.

Like many projects based on the Pico SDK, this project includes [CMake
code](pico_sdk_import.cmake) that integrates the SDK into the
build. This usually requires that the path of the SDK is in the
`PICO_SDK_PATH` environment variable, or it may be passed in as a `-D`
command-line definition in the `cmake` command shown below. See the
[docs](https://datasheets.raspberrypi.com/picow/connecting-to-the-internet-with-pico-w.pdf)
for details. In the following, we will assume that `PICO_SDK_PATH` is
set in the environment.

In the project repo, create a build subdirectory, and call `cmake` in
that directory:

```shell
$ cd picow-http-example
$ mkdir build
$ cd build
$ cmake -DPICO_BOARD=pico_w -DWIFI_SSID=my_wifi -DWIFI_PASSWORD=wifi_pass ..
```

The three `-D` command-line options in the `cmake` invocation shown
above are required. `PICO_BOARD=pico_w` identifies the PicoW for the
SDK as the target hardware. This project follows the PicoW examples in
the [`pico-examples`](https://github.com/raspberrypi/pico-examples)
repository by setting WiFi credentials via CMake definitions. Set
`WIFI_SSID` to the SSID of the access point (the network name of your
WiFi router), and `WIFI_PASSWORD` to its password.

There are two optional parameters for `-D` on the `cmake` command line:

  * `HOSTNAME`: host name for the PicoW
  * `NTP_SERVER`: server to be used for [time
    synchronization](https://slimhazard.gitlab.io/picow_http/group__ntp.html)

If you set `HOSTNAME=my_host`, the HTTP server can be reached after
deployment at `http://my_host`. The default hostname is `PicoW`.

The default value of `NTP_SERVER` is a generic pool; it is usually
much better to specify an NTP server or pool that is "closer" to the
location where the PicoW will be deployed. If your WiFi router
provides NTP synchronization, then that is the ideal choice.

This invocation of `cmake` specifies both optional parameters:

```shell
# Set the hostname to picow-sample, and use the regional NTP server pool
# in Germany.
$ cmake -DPICO_BOARD=pico_w -DWIFI_SSID=my_wifi -DWIFI_PASSWORD=wifi_pass \
        -DHOSTNAME=picow-sample -DNTP_SERVER=de.pool.ntp.org ..
```

After the `cmake` call, the software is built with `make`:

```shell
$ make -j
```

If all goes well, then you have now built binaries that are ready to
deploy.

### Deploying the app

This project builds _two_ versions of the binary:

  * `picow-http-example-background`
  * `picow-http-example-poll`

These use the two network architectures that are currently supported
by picow-http: threadsafe background mode and poll mode; see the [SDK
docs](https://raspberrypi.github.io/pico-sdk-doxygen/group__pico__cyw43__arch.html)
for details. The two versions are otherwise identical. Most
applications will choose just one network architecture, but the
example app shows how to use either of them.

After a successful invocation of `make`, the build directory contains
the binary artifacts for the two versions. These can be loaded on the
PicoW in any of the usual ways for a PicoW or Pico; for example by
copying the `*.uf2` file to the `RPI-RP2` USB device that is presented
when the board is in boot select mode. See the [Getting
Started](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
document for details.

If you are using a picoprobe (see Appendix A in Getting Started), the
build environment [defines](picoprobe_targets.cmake) two targets that
flash the binaries to the PicoW:

```shell
# For use with a picoprobe
$ make flash-picow-http-example-background

# or:
$ make flash-picow-http-example-poll
```

These commands encapsulate the `openocd` calls that load the binary code.

After loading the binary, point a browser to `http://picow` (or a URL
with the `HOSTNAME` defined in the `cmake` invocation as shown above)
to view the application.

### Monitoring the log

The application is configured to use
[UART](https://raspberrypi.github.io/pico-sdk-doxygen/group__pico__stdio__uart.html)
for log output. The means of viewing UART output are platform
dependent; see the [Getting
Started](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
document for suggestions that apply to Linux, MacOS and Windows.

When the application starts up after load, the log output is similar
to:

```
Connecting to my_wifi ...
Connected to my_wifi
http started
192.168.1.1 - - [27/Oct/2022:20:40:10 +0000] "GET / HTTP/1.1" 200 729
192.168.1.1 - - [27/Oct/2022:20:40:10 +0000] "GET /sample_app.js HTTP/1.1" 200 1497
192.168.1.1 - - [27/Oct/2022:20:40:10 +0000] "GET /picow.css HTTP/1.1" 200 506
192.168.1.1 - - [27/Oct/2022:20:40:10 +0000] "GET /temp HTTP/1.1" 200 7
192.168.1.1 - - [27/Oct/2022:20:40:10 +0000] "GET /img/favicon.png HTTP/1.1" 200 255
192.168.1.1 - - [27/Oct/2022:20:40:10 +0000] "GET /led HTTP/1.1" 200 1
192.168.1.1 - - [27/Oct/2022:20:40:10 +0000] "GET /rssi HTTP/1.1" 200 28
```

By default, request logs in [Common Log
Format](https://en.wikipedia.org/wiki/Common_Log_Format) are emitted with dates and
times in the [UTC time zone](https://en.wikipedia.org/wiki/Coordinated_Universal_Time)
(and hence the time zone offset is always `+0000`). See the [log API
docs](https://slimhazard.gitlab.io/picow_http/group__log.html) for details about
setting the log verbosity at compile time in a picow-http application.
