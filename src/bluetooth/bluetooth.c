#include <pebble.h>
#include "bluetooth.h"
#include "../main_window.h"
#include "../weather/weather.h"
#include "../configuration/settings.h"

void bluetooth_status_update(bool connected, bool startup) {
  if (!connected) {
    if (vibe_disconnect == 1 && startup == false) vibes_long_pulse();


    if (language == 0) {
      text_layer_set_text(top_bt_layer, "NO");
      text_layer_set_text(btm_bt_layer, "CONNECTION");
    } else if (language == 1) {
      text_layer_set_text(top_bt_layer, "pas de");
      text_layer_set_text(btm_bt_layer, "CONNECTION");
    } else if (language == 2) {
      text_layer_set_text(top_bt_layer, "sin");
      text_layer_set_text(btm_bt_layer, "conexión");
    } else if (language == 3) {
      text_layer_set_text(top_bt_layer, "keine");
      text_layer_set_text(btm_bt_layer, "Verbindung");
    } else {
      text_layer_set_text(top_bt_layer, "NO");
      text_layer_set_text(btm_bt_layer, "CONNECTION");
    }

    size_weather();

    layer_set_hidden(text_layer_get_layer(temperature_layer), true);
    layer_set_hidden(text_layer_get_layer(conditions_layer), true);
    layer_set_hidden(text_layer_get_layer(top_bt_layer), false);
    layer_set_hidden(text_layer_get_layer(btm_bt_layer), false);

  } else {
    if (vibe_connect == 1 && startup == false) vibes_double_pulse();

    layer_set_hidden(text_layer_get_layer(temperature_layer), false);
    layer_set_hidden(text_layer_get_layer(conditions_layer), false);
    layer_set_hidden(text_layer_get_layer(top_bt_layer), true);
    layer_set_hidden(text_layer_get_layer(btm_bt_layer), true);

    if (startup == false) update_weather(); // Fetch weather now that phone is connected
  }
}

void bluetooth_handler(bool connected) {
  bluetooth_status_update(connected, false);
}
