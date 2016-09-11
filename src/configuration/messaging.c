#include <pebble.h>
#include "messaging.h"
#include "settings.h"
#include "colours.h"
#include "../main_window.h"
#include "../weather/weather.h"
#include "../lang/lang.h"

static void inbox_recv_handler(DictionaryIterator *iter, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Received messageKeys");

  bool weather_needs_update = false;
  bool conf_vibe = true;

  Tuple *t = dict_read_first(iter);
  while(t) {
    int true_key = t->key - 10000;

    // Deal with weather keys first
    if (true_key == CfgKeyTemperature) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Received temperature in Fahrenheit");
      snprintf(temp_buffer, sizeof(temp_buffer), "%d°", (int)t->value->int32);
      weather_needs_update = false;
      conf_vibe = false;
    }

    if (true_key == CfgKeyCelsiusTemperature) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Received temperature in Celsius");
      snprintf(temp_c_buffer, sizeof(temp_c_buffer), "%d°", (int)t->value->int32);
      weather_needs_update = false;
      conf_vibe = false;
    }

    if (true_key == CfgKeyConditions) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Received conditions");
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
      weather_needs_update = false;
      conf_vibe = false;
    }

    // Since some of the keys aren't booleans, we check for them here and deal with them accordingly
    if (true_key == CfgKeyWeatherMode) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting weather_mode");

      //last_weather_mode = weather_mode;
      weather_mode = atoi(t->value->cstring);

      if (weather_mode == 0) {
        weather_needs_update = true;
      }
    }

    if (true_key == CfgKeyWeatherLocation) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Received weather_location");
    }

    if (true_key == CfgKeyLanguage) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting language");

      last_language = language;
      language = atoi(t->value->cstring);

      if (language != last_language) {
        weather_needs_update = true;
      }
    }

    if (true_key == CfgKeyBackgroundColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting background_colour");
      background_colour = t->value->int32;
    }

    if (true_key == CfgKeyTextColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting text_colour");
      text_colour = t->value->int32;
    }

    if (true_key == CfgKeyMiddleBarMode) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting middle_bar_mode");
      middle_bar_mode = atoi(t->value->cstring);
    }

    if (true_key == CfgKeyManualStepGoal) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting manual_step_goal");
      manual_step_goal = t->value->int32;
    }

    if (true_key == CfgKeyNightModeStart) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting night_start_hour");
      night_start_hour = atoi(t->value->cstring);
    }

    if (true_key == CfgKeyNightModeEnd) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting night_end_hour");
      night_end_hour = atoi(t->value->cstring);
    }

    if (true_key == CfgKeyNightBackgroundColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting night_background_colour");
      night_background_colour = t->value->int32;
    }

    if (true_key == CfgKeyNightTextColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting night_text_colour");
      night_text_colour = t->value->int32;
    }

    // We want the config array to stay the correct size, so we still parse every setting
    parse_settings(true_key, t->value->int32);
    t = dict_read_next(iter);
  }

  // All done receiving settings, vibrate to notify the user
  if (conf_vibe) vibes_double_pulse();

  // Then update everything that needs updating
  update_colours();
  update_time();

  if (weather_needs_update) { // If this is false is that the only time we need to display_weather? Would save doing that every time we receive appmessages
    update_weather();
  } else {
    display_weather();
  }

  layer_mark_dirty(middle_bar_layer);
}

void init_messaging() {
  app_message_register_inbox_received(inbox_recv_handler); // TO DO: Other handlers for dropped msgs, etc
  app_message_open(128, 128); // TO DO: Calculate buffer based on array size
}
