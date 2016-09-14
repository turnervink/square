#include <pebble.h>
#include "bluetooth.h"
#include "../main_window.h"
#include "../weather/weather.h"
#include "../configuration/settings.h"

void bluetooth_handler(bool connected) {
  if (!connected) {
    vibes_long_pulse();

    if (language == 0) {
      text_layer_set_text(temperature_layer, "NO");
      text_layer_set_text(conditions_layer, "CONNECTION");
    } else if (language == 1) {
      text_layer_set_text(temperature_layer, "pas de");
      text_layer_set_text(conditions_layer, "CONNECTION");
    } else if (language == 2) {
      text_layer_set_text(temperature_layer, "sin");
      text_layer_set_text(conditions_layer, "conexión");
    } else if (language == 3) {
      text_layer_set_text(temperature_layer, "keine");
      text_layer_set_text(conditions_layer, "Verbindung");
    } else {
      text_layer_set_text(temperature_layer, "NO");
      text_layer_set_text(conditions_layer, "CONNECTION");
    }

  } else {
    vibes_double_pulse();
    text_layer_set_text(temperature_layer, "");
    text_layer_set_text(conditions_layer, "");
    update_weather();
  }
}
