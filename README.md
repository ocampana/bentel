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
