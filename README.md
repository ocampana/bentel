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
  * Information about the PicoW's network connection:
    * hostname
    * IP address
    * MAC address
    * SSID of the WiFi access point
    * [rssi](https://en.wikipedia.org/wiki/Received_signal_strength_indication)
      / signal strength of the access point

While the app is visible in a browser window, the temperature and rssi
measurements are updated every few seconds.

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

# Build/Install

## Requirements

The [Pico C SDK](https://raspberrypi.github.io/pico-sdk-doxygen/index.html)
and its toolchain are required to build the app. picow-http also requires
some [additional
software](https://gitlab.com/slimhazard/picow_http/-/wikis/required-software);
see the link (at the [picow-http project
Wiki](https://gitlab.com/slimhazard/picow_http/-/wikis/home)) for details.

## Building the app

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
command-line definition in the `cmake` command shown below. With one
of these options, the SDK is integrated transparently when `cmake` is
invoked. See the
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
