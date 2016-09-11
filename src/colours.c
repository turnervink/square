#include <pebble.h>
#include "main_window.h"
#include "configuration/settings.h"
#include "logs.h"

bool use_night_mode() {
  time_t temp = time(NULL);
	struct tm *tick_time = localtime(&temp);
	int cur_hour = tick_time->tm_hour;

  if (get_settings(CfgKeyUseNightMode)) {
    #ifdef SHOW_COLOURS_LOGS
    APP_LOG(APP_LOG_LEVEL_INFO, "CfgKeyUseNightMode is true");
    #endif
    if (night_end_hour < night_start_hour) {
      // The range crosses midnight
      #ifdef SHOW_COLOURS_LOGS
      APP_LOG(APP_LOG_LEVEL_INFO, "The night range crosses midnight");
      #endif
      if (cur_hour >= night_start_hour) {
        #ifdef SHOW_COLOURS_LOGS
        APP_LOG(APP_LOG_LEVEL_INFO, "We're past the start, but not midnight");
        #endif
        return true;
      } else if (cur_hour >= 0 && cur_hour < night_end_hour) {
        #ifdef SHOW_COLOURS_LOGS
        APP_LOG(APP_LOG_LEVEL_INFO, "Past midnight but before the end");
        #endif
        return true;
      } else {
        #ifdef SHOW_COLOURS_LOGS
        APP_LOG(APP_LOG_LEVEL_INFO, "We're not in the range");
        #endif
        return false;
      }
    } else {
      #ifdef SHOW_COLOURS_LOGS
      APP_LOG(APP_LOG_LEVEL_INFO, "The night range does not cross midnight");
      #endif
      if (cur_hour >= night_start_hour && cur_hour < night_end_hour) {
        #ifdef SHOW_COLOURS_LOGS
        APP_LOG(APP_LOG_LEVEL_INFO, "We're in the range");
        #endif
        return true;
      } else {
        #ifdef SHOW_COLOURS_LOGS
        APP_LOG(APP_LOG_LEVEL_INFO, "We're not in the range");
        #endif
        return false;
      }
    }
  } else {
    return false;
  }
}

void update_colours() {
  #ifdef PBL_COLOR

  if (use_night_mode()) {
    // Use night mode colours
    text_layer_set_text_color(time_layer, GColorFromHEX(night_text_colour));
    text_layer_set_text_color(date_layer, GColorFromHEX(night_text_colour));
    text_layer_set_text_color(temperature_layer, GColorFromHEX(night_text_colour));
    text_layer_set_text_color(conditions_layer, GColorFromHEX(night_text_colour));

    window_set_background_color(main_window, GColorFromHEX(night_background_colour));
  } else {
    // Use day mode colours
    text_layer_set_text_color(time_layer, GColorFromHEX(text_colour));
    text_layer_set_text_color(date_layer, GColorFromHEX(text_colour));
    text_layer_set_text_color(temperature_layer, GColorFromHEX(text_colour));
    text_layer_set_text_color(conditions_layer, GColorFromHEX(text_colour));

    window_set_background_color(main_window, GColorFromHEX(background_colour));
  }

  #else

  if (get_settings(CfgKeyInvertColours)) {
    text_layer_set_text_color(time_layer, GColorBlack);
    text_layer_set_text_color(date_layer, GColorBlack);
    text_layer_set_text_color(temperature_layer, GColorBlack);
    text_layer_set_text_color(conditions_layer, GColorBlack);

    window_set_background_color(main_window, GColorWhite);
  } else {
    text_layer_set_text_color(time_layer, GColorWhite);
    text_layer_set_text_color(date_layer, GColorWhite);
    text_layer_set_text_color(temperature_layer, GColorWhite);
    text_layer_set_text_color(conditions_layer, GColorWhite);

    window_set_background_color(main_window, GColorBlack);
  }

  #endif
}
