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

    GRect bounds = layer_get_bounds(window_get_root_layer(main_window));
    GRect time_frame = layer_get_frame(text_layer_get_layer(time_layer));
  	GSize date_size = text_layer_get_content_size(date_layer);
  	GRect date_frame = layer_get_frame(text_layer_get_layer(date_layer));

    GSize top_bt_size = text_layer_get_content_size(top_bt_layer);
    GSize btm_bt_size = text_layer_get_content_size(btm_bt_layer);

    #ifdef PBL_ROUND
    int round_temp_offset;
    if (show_seconds == 1) {
      round_temp_offset = 5;
    } else {
      round_temp_offset = 10;
    }
    #endif

    layer_set_frame(text_layer_get_layer(top_bt_layer), GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(time_frame.origin.y - top_bt_size.h + round_temp_offset, 0), 144, top_bt_size.h));
    layer_set_frame(text_layer_get_layer(btm_bt_layer), GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(date_frame.origin.y + date_size.h, bounds.size.h - btm_bt_size.h - 5), 144, btm_bt_size.h));

    layer_set_hidden(text_layer_get_layer(temperature_layer), true);
    layer_set_hidden(text_layer_get_layer(conditions_layer), true);
    layer_set_hidden(text_layer_get_layer(top_bt_layer), false);
    layer_set_hidden(text_layer_get_layer(btm_bt_layer), false);

  } else {
    if (vibe_connect == 1 && startup == false) vibes_double_pulse();

    if (weather_mode != 2) { // Keep weather hidden if necessary
      layer_set_hidden(text_layer_get_layer(temperature_layer), false);
      layer_set_hidden(text_layer_get_layer(conditions_layer), false);
    }
    layer_set_hidden(text_layer_get_layer(top_bt_layer), true);
    layer_set_hidden(text_layer_get_layer(btm_bt_layer), true);

    if (startup == false) update_weather(); // Fetch weather now that phone is connected
  }
}

void bluetooth_handler(bool connected) {
  bluetooth_status_update(connected, false);
}
