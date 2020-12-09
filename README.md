# esp32_control_panel
A web control panel for esp32

## How the slider works
Sends a GET request on route `/led_value/<value from 0 - 255>` on each `slide` event.