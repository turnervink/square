#include <pebble.h>
#include "main_window.h"
#include "middle_bar.h"
#include "configuration/settings.h"
#include "lang/lang.h"
#include "weather/weather.h"
#include "bluetooth/bluetooth.h"
#include "logs.h"

Window *main_window;
TextLayer *time_layer, *date_layer, *temperature_layer, *conditions_layer;
Layer *middle_bar_layer;
GFont time_font, small_time_font, date_font, lg_weather_font, sm_weather_font;


void size_time_layers() {
  GRect bounds = layer_get_bounds(window_get_root_layer(main_window));

  if (show_seconds == 1) {
    text_layer_set_font(time_layer, small_time_font);
  } else {
    text_layer_set_font(time_layer, time_font);
  }

  GSize time_size = text_layer_get_content_size(time_layer);
  layer_set_frame(text_layer_get_layer(time_layer), GRect(0, ((bounds.size.h / 2) + 5 - time_size.h), bounds.size.w, time_size.h));

  GSize date_size = text_layer_get_content_size(date_layer);
  layer_set_frame(text_layer_get_layer(date_layer), GRect(0, (bounds.size.h / 2) + 5, bounds.size.w, date_size.h));
}

void update_time() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  static char time_buffer[] = "00:00:00";
  static char date_num_buffer[] = "DD";
  static char full_date_buffer[] = "WWW DD MMM";

  #ifdef SCREENSHOT_MODE
    if (show_seconds == 1) {
      snprintf(time_buffer, sizeof("00:00:00"), "%s", "12:35:01");
    } else {
      snprintf(time_buffer, sizeof("00:00:00"), "%s", "12:35");
    }
  #else
  if (show_seconds == 1) {
    if (clock_is_24h_style() == true) {
  		strftime(time_buffer, sizeof("00:00:00"), "%H:%M:%S", tick_time);
  	} else {
  		strftime(time_buffer, sizeof("00:00:00"), "%I:%M:%S", tick_time);
  	}
  } else {
    if (clock_is_24h_style() == true) {
  		strftime(time_buffer, sizeof("00:00:00"), "%H:%M", tick_time);
  	} else {
  		strftime(time_buffer, sizeof("00:00:00"), "%I:%M", tick_time);
  	}
  }
  #endif

	text_layer_set_text(time_layer, time_buffer);

  int month = tick_time->tm_mon;
	int weekday = tick_time->tm_wday;
  strftime(date_num_buffer, sizeof("DD"), "%d", tick_time);

  #ifdef SCREENSHOT_MODE
    snprintf(full_date_buffer, sizeof(full_date_buffer), "%s", "THU APR 2");
  #else
  if (euro_date == 1) {
    snprintf(full_date_buffer, sizeof(full_date_buffer), "%s %s %s", dayNames[language][weekday], date_num_buffer, monthNames[language][month]);
  } else {
    snprintf(full_date_buffer, sizeof(full_date_buffer), "%s %s %s", dayNames[language][weekday], monthNames[language][month], date_num_buffer);
  }
  #endif

  text_layer_set_text(date_layer, full_date_buffer);

  // Mark the middle bar dirty to be sure we update the colours when entering night mode
  layer_mark_dirty(middle_bar_layer);
}

static void main_window_load(Window *window) {
  GRect bounds = layer_get_bounds(window_get_root_layer(window));
  Layer *window_layer = window_get_root_layer(window);

  // Create fonts
  time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_50));
  small_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_34));
  date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_26));
  sm_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_14));
  lg_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_SQUARE_18));


  time_layer = text_layer_create(GRect(0, 0, bounds.size.h, bounds.size.h));
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);

  date_layer = text_layer_create(GRect(0, 0, bounds.size.h, bounds.size.h));
  text_layer_set_background_color(date_layer, GColorClear);
  text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
  text_layer_set_font(date_layer, date_font);

  middle_bar_layer = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  layer_set_update_proc(middle_bar_layer, middle_bar_update_proc);

  GRect time_frame = layer_get_frame(text_layer_get_layer(time_layer));
	GSize date_size = text_layer_get_content_size(date_layer);
	GRect date_frame = layer_get_frame(text_layer_get_layer(date_layer));

  temperature_layer = text_layer_create(GRect(0, 0, 144, 168));
  text_layer_set_background_color(temperature_layer, GColorClear);
  text_layer_set_text_alignment(temperature_layer, GTextAlignmentCenter);
  text_layer_set_font(temperature_layer, lg_weather_font);

  conditions_layer = text_layer_create(GRect(0, 0, 144, 168));
  text_layer_set_overflow_mode(conditions_layer, GTextOverflowModeWordWrap);
  text_layer_set_background_color(conditions_layer, GColorClear);
  text_layer_set_text_alignment(conditions_layer, GTextAlignmentCenter);
  text_layer_set_font(conditions_layer, lg_weather_font);

  layer_add_child(window_layer, text_layer_get_layer(time_layer));
  layer_add_child(window_layer, text_layer_get_layer(date_layer));
  layer_add_child(window_layer, middle_bar_layer);
  layer_add_child(window_layer, text_layer_get_layer(temperature_layer));
  layer_add_child(window_layer, text_layer_get_layer(conditions_layer));

  load_settings();

  update_time();
  update_colours();
  size_time_layers();

  bool connected = bluetooth_connection_service_peek();

  bluetooth_status_update(connected, true);
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
