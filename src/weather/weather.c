#include <pebble.h>
#include "../main_window.h"
#include "../configuration/settings.h"

char temp_buffer[15];
char temp_c_buffer[15];
char conditions_buffer[100];
// TODO Size these buffers properly

void update_weather() {
  if (weather_mode == 0) { // If displaying weather, fetch it
    APP_LOG(APP_LOG_LEVEL_INFO, "Requesting weather update");

    // Blank out old weather info (Can/should we clear the buffer too?)
    text_layer_set_text(temperature_layer, "");
    text_layer_set_text(conditions_layer, "");

  	DictionaryIterator *iter;
  	app_message_outbox_begin(&iter);

  	dict_write_uint8(iter, MESSAGE_KEY_CfgKeyConditions, 0);
  	app_message_outbox_send();
  } else { // Else don't fetch it
    APP_LOG(APP_LOG_LEVEL_INFO, "Weather was requested but is hidden, not fetching");
  }
}

void display_weather() {
  APP_LOG(APP_LOG_LEVEL_INFO, "Displaying weather");
  text_layer_set_text(temperature_layer, temp_c_buffer);
  text_layer_set_text(conditions_layer, conditions_buffer);

  APP_LOG(APP_LOG_LEVEL_INFO, "Sizing weather layers");

  GRect bounds = layer_get_bounds(window_get_root_layer(main_window));
  GRect time_frame = layer_get_frame(text_layer_get_layer(time_layer));
	GSize date_size = text_layer_get_content_size(date_layer);
	GRect date_frame = layer_get_frame(text_layer_get_layer(date_layer));

  GSize temperature_size = text_layer_get_content_size(temperature_layer);
  GSize conditions_size = text_layer_get_content_size(conditions_layer);

  APP_LOG(APP_LOG_LEVEL_INFO, "Temp height: %d", temperature_size.h);
  APP_LOG(APP_LOG_LEVEL_INFO, "Conditions height: %d", conditions_size.h);

  #ifdef PBL_ROUND
  int round_temp_offset;
  if (show_seconds == 1) {
    round_temp_offset = 5;
  } else {
    round_temp_offset = 10;
  }
  #endif

  layer_set_frame(text_layer_get_layer(temperature_layer), GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(time_frame.origin.y - temperature_size.h + round_temp_offset, 0), 144, temperature_size.h));
  layer_set_frame(text_layer_get_layer(conditions_layer), GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(date_frame.origin.y + date_size.h, bounds.size.h - conditions_size.h - 5), 144, conditions_size.h));

  if (weather_mode == 0) {
    // Show layers
    APP_LOG(APP_LOG_LEVEL_INFO, "Showing weather");
    layer_set_hidden(text_layer_get_layer(temperature_layer), false);
    layer_set_hidden(text_layer_get_layer(conditions_layer), false);
  } else if (weather_mode == 2) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Hiding weather");
    layer_set_hidden(text_layer_get_layer(temperature_layer), true);
    layer_set_hidden(text_layer_get_layer(conditions_layer), true);
  } else {
    APP_LOG(APP_LOG_LEVEL_INFO, "Else Showing weather");
    layer_set_hidden(text_layer_get_layer(temperature_layer), false);
    layer_set_hidden(text_layer_get_layer(conditions_layer), false);
  }
}
