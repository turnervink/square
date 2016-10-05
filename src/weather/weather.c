#include <pebble.h>
#include "../main_window.h"
#include "../configuration/settings.h"
#include "../logs.h"

char temp_buffer[15];
char temp_c_buffer[15];
char conditions_buffer[100];

bool scheduled = false;

void on_animation_stopped(Animation *anim, bool finished, void *context) {
    //Free the memory used by the Animation
    property_animation_destroy((PropertyAnimation*) anim);
    scheduled = false;
}

void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration, int delay) {
    //Declare animation
    PropertyAnimation *anim = property_animation_create_layer_frame(layer, start, finish);

    //Set characteristics
    animation_set_duration((Animation*) anim, duration);
    animation_set_delay((Animation*) anim, delay);

    //Set stopped handler to free memory
    AnimationHandlers handlers = {
        //The reference to the stopped handler is the only one in the array
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);

    //Start animation!
    animation_schedule((Animation*) anim);
    scheduled = true; // Prevent multiple animations from happening at once
}

void animate_weather() {
  GRect bounds = layer_get_bounds(window_get_root_layer(main_window));
  GRect time_frame = layer_get_frame(text_layer_get_layer(time_layer));
	GSize date_size = text_layer_get_content_size(date_layer);
	GRect date_frame = layer_get_frame(text_layer_get_layer(date_layer));

  GSize temperature_size = text_layer_get_content_size(temperature_layer);
  GSize conditions_size = text_layer_get_content_size(conditions_layer);

  #ifdef PBL_ROUND
  int round_temp_offset;
  if (show_seconds == 1) {
    round_temp_offset = 5;
  } else {
    round_temp_offset = 10;
  }
  #endif

  GRect temperature_offscreen = GRect(PBL_IF_ROUND_ELSE(18, 0), 0 - conditions_size.h, 144, temperature_size.h);
  GRect conditions_offscreen = GRect(PBL_IF_ROUND_ELSE(18, 0), bounds.size.h + conditions_size.h, 144, conditions_size.h);
  GRect temperature_onscreen = GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(time_frame.origin.y - temperature_size.h + round_temp_offset, 0), 144, temperature_size.h);
  GRect conditions_onscreen =  GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(date_frame.origin.y + date_size.h, bounds.size.h - conditions_size.h - 5), 144, conditions_size.h);

  if (!scheduled) {
    animate_layer(text_layer_get_layer(temperature_layer), &temperature_offscreen, &temperature_onscreen, 1000, 0);
    animate_layer(text_layer_get_layer(conditions_layer), &conditions_offscreen, &conditions_onscreen, 1000, 0);

    animate_layer(text_layer_get_layer(temperature_layer), &temperature_onscreen, &temperature_offscreen, 1000, 5000);
    animate_layer(text_layer_get_layer(conditions_layer), &conditions_onscreen, &conditions_offscreen, 1000, 5000);
  }
}

void accel_handler(AccelAxisType axis, int32_t direction) {
  if (weather_mode == 1) {
    animate_weather();
  }
}

void update_weather() {
  if (weather_mode != 2) { // If displaying weather, fetch it
    APP_LOG(APP_LOG_LEVEL_INFO, "Requesting weather update");

    // Blank out old weather info (Can/should we clear the buffer too?)
    text_layer_set_text(temperature_layer, "");
    text_layer_set_text(conditions_layer, "");

  	DictionaryIterator *iter;
  	app_message_outbox_begin(&iter);

  	dict_write_uint8(iter, MESSAGE_KEY_CfgKeyConditions, 0);
  	app_message_outbox_send();
  } else { // Else don't fetch it
    APP_LOG(APP_LOG_LEVEL_WARNING, "Weather was requested but is hidden, not fetching");
  }
}

void size_weather() {
  #ifdef DEBUG_MODE
  APP_LOG(APP_LOG_LEVEL_INFO, "Sizing weather layers");
  #endif

  GRect bounds = layer_get_bounds(window_get_root_layer(main_window));
  GRect time_frame = layer_get_frame(text_layer_get_layer(time_layer));
	GSize date_size = text_layer_get_content_size(date_layer);
	GRect date_frame = layer_get_frame(text_layer_get_layer(date_layer));

  GSize temperature_size = text_layer_get_content_size(temperature_layer);
  GSize conditions_size = text_layer_get_content_size(conditions_layer);

  #ifdef DEBUG_MODE
  APP_LOG(APP_LOG_LEVEL_INFO, "Temp height: %d", temperature_size.h);
  APP_LOG(APP_LOG_LEVEL_INFO, "Conditions height: %d", conditions_size.h);
  #endif

  #ifdef PBL_ROUND
  int round_temp_offset;
  if (show_seconds == 1) {
    round_temp_offset = 5;
  } else {
    round_temp_offset = 10;
  }
  #endif

  // Set frame to offscreen if shaking to show
  if (weather_mode == 1) {
    layer_set_frame(text_layer_get_layer(temperature_layer), GRect(PBL_IF_ROUND_ELSE(18, 0), 0 - conditions_size.h, 144, temperature_size.h));
    layer_set_frame(text_layer_get_layer(conditions_layer), GRect(PBL_IF_ROUND_ELSE(18, 0), bounds.size.h + conditions_size.h, 144, conditions_size.h));
  } else {
    layer_set_frame(text_layer_get_layer(temperature_layer), GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(time_frame.origin.y - temperature_size.h + round_temp_offset, 0), 144, temperature_size.h));
    layer_set_frame(text_layer_get_layer(conditions_layer), GRect(PBL_IF_ROUND_ELSE(18, 0), PBL_IF_ROUND_ELSE(date_frame.origin.y + date_size.h, bounds.size.h - conditions_size.h - 5), 144, conditions_size.h));
  }
}

void display_weather() {
  #ifdef DEBUG_MODE
  APP_LOG(APP_LOG_LEVEL_INFO, "Displaying weather");
  #endif

  #ifdef SCREENSHOT_MODE
  text_layer_set_text(temperature_layer, "78°");
  text_layer_set_text(conditions_layer, "Partly Cloudy");
  #else
  if (use_celsius == 1) {
    text_layer_set_text(temperature_layer, temp_c_buffer);
  } else {
    text_layer_set_text(temperature_layer, temp_buffer);
  }

  text_layer_set_text(conditions_layer, conditions_buffer);
  #endif

  size_weather();

  if (weather_mode == 0) {
    // Show layers
    #ifdef DEBUG_MODE
    APP_LOG(APP_LOG_LEVEL_INFO, "Showing weather");
    #endif
    layer_set_hidden(text_layer_get_layer(temperature_layer), false);
    layer_set_hidden(text_layer_get_layer(conditions_layer), false);
  } else if (weather_mode == 2) {
    #ifdef DEBUG_MODE
    APP_LOG(APP_LOG_LEVEL_INFO, "Hiding weather");
    #endif
    layer_set_hidden(text_layer_get_layer(temperature_layer), true);
    layer_set_hidden(text_layer_get_layer(conditions_layer), true);
  } else {
    APP_LOG(APP_LOG_LEVEL_WARNING, "Else Showing weather");
    layer_set_hidden(text_layer_get_layer(temperature_layer), false);
    layer_set_hidden(text_layer_get_layer(conditions_layer), false);
  }
}
