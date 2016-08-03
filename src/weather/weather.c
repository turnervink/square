#include <pebble.h>
#include "../main_window.h"

char temp_buffer[15];
char temp_c_buffer[15];
char conditions_buffer[100];
// TODO Size these buffers properly

void update_weather() {
  APP_LOG(APP_LOG_LEVEL_INFO, "Requesting weather update");

	DictionaryIterator *iter;
	app_message_outbox_begin(&iter);

	dict_write_uint8(iter, 0, 0);
	app_message_outbox_send();
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

  layer_set_frame(text_layer_get_layer(temperature_layer), GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(time_frame.origin.y, 0), 144, temperature_size.h));
  layer_set_frame(text_layer_get_layer(conditions_layer), GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(date_frame.origin.y, bounds.size.h - conditions_size.h - 5), 144, conditions_size.h));
}

void size_weather_layers() {

}
