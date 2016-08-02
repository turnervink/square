#include <pebble.h>
#include "main_window.h"
#include "configuration/settings.h"
#include "lang/lang.h"

Window *main_window;
TextLayer *time_layer, *date_layer, *temperature_layer, *conditions_layer;
Layer *middle_bar_layer;
GFont time_font, date_font, lg_weather_font, sm_weather_font;



void size_time_layers() {
  GRect bounds = layer_get_bounds(window_get_root_layer(main_window));

  GSize time_size = text_layer_get_content_size(time_layer);
  layer_set_frame(text_layer_get_layer(time_layer), GRect(0, ((bounds.size.h / 2) + 5 - time_size.h), bounds.size.w, time_size.h));

  GSize date_size = text_layer_get_content_size(date_layer);
  layer_set_frame(text_layer_get_layer(date_layer), GRect(0, (bounds.size.h / 2) + 5, bounds.size.w, bounds.size.h));
}

void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  static char time_buffer[] = "00:00:00";
  static char date_num_buffer[] = "DD";
  static char full_date_buffer[] = "WWW DD MMM";

	if(clock_is_24h_style() == true) {
		strftime(time_buffer, sizeof("00:00:00"), "%H:%M", tick_time);
	} else {
		strftime(time_buffer, sizeof("00:00:00"), "%I:%M", tick_time);
	}

	text_layer_set_text(time_layer, time_buffer);

  int month = tick_time->tm_mon;
	int weekday = tick_time->tm_wday;
  strftime(date_num_buffer, sizeof("DD"), "%d", tick_time);

  if (get_settings(CfgKeyEuropeanDate)) {
    snprintf(full_date_buffer, sizeof(full_date_buffer), "%s %s %s", dayNames[language][weekday], date_num_buffer, monthNames[language][month]);
  } else {
    snprintf(full_date_buffer, sizeof(full_date_buffer), "%s %s %s", dayNames[language][weekday], monthNames[language][month], date_num_buffer);
  }

  text_layer_set_text(date_layer, full_date_buffer);

  // Mark the middle bar dirty to be sure we update the colours when entering night mode
  layer_mark_dirty(middle_bar_layer);
}

static void main_window_load(Window *window) {
  GRect bounds = layer_get_bounds(window_get_root_layer(window));
  Layer *window_layer = window_get_root_layer(window);

  // Create fonts
  time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_50));
  date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_26));
  sm_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_14));
  lg_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_18));


  time_layer = text_layer_create(GRect(0, 0, bounds.size.h, bounds.size.h));
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  text_layer_set_font(time_layer, time_font);

  date_layer = text_layer_create(GRect(0, 0, bounds.size.h, bounds.size.h));
  text_layer_set_background_color(date_layer, GColorClear);
  text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
  text_layer_set_font(date_layer, date_font);

  middle_bar_layer = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  layer_set_update_proc(middle_bar_layer, middle_bar_update_proc);

  GRect time_frame = layer_get_frame(text_layer_get_layer(time_layer));
	GSize date_size = text_layer_get_content_size(date_layer);
	GRect date_frame = layer_get_frame(text_layer_get_layer(date_layer));

  temperature_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(time_frame.origin.y - 4, 0), 144, 18));
  text_layer_set_background_color(temperature_layer, GColorClear);
  text_layer_set_text_alignment(temperature_layer, GTextAlignmentCenter);
  text_layer_set_font(temperature_layer, sm_weather_font);
  text_layer_set_text(temperature_layer, "24°");

  conditions_layer = text_layer_create(GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(date_frame.origin.y + date_size.h, bounds.size.h - 23), 144, 18));
  text_layer_set_background_color(conditions_layer, GColorClear);
  text_layer_set_text_alignment(conditions_layer, GTextAlignmentCenter);
  text_layer_set_font(conditions_layer, sm_weather_font);
  text_layer_set_text(conditions_layer, "few clouds");

  layer_add_child(window_layer, text_layer_get_layer(time_layer));
  layer_add_child(window_layer, text_layer_get_layer(date_layer));
  layer_add_child(window_layer, middle_bar_layer);
  layer_add_child(window_layer, text_layer_get_layer(temperature_layer));
  layer_add_child(window_layer, text_layer_get_layer(conditions_layer));

  load_settings();

  update_time();
  update_colours(); // Something isn't working here if we load up while in night mode
  size_time_layers();
}

static void main_window_unload(Window *window) {

}



void main_window_push() {
  main_window = window_create();

  window_set_window_handlers(main_window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload
	});

	window_stack_push(main_window, true);
}
