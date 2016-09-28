#include <pebble.h>
#include "messaging.h"
#include "settings.h"
#include "colours.h"
#include "../main_window.h"
#include "../weather/weather.h"
#include "../lang/lang.h"
#include "../logs.h"

static void inbox_recv_handler(DictionaryIterator *iter, void *ctx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Received messageKeys");

  bool weather_needs_update = false;
  bool conf_vibe = true;

  Tuple *t = dict_read_first(iter);
  while(t) {
    int true_key = t->key - 10000;

    // Deal with weather keys first
    if (true_key == CfgKeyTemperature) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Received temperature in Fahrenheit");
      #endif
      snprintf(temp_buffer, sizeof(temp_buffer), "%d°", (int)t->value->int32);
      //weather_needs_update = false;
      conf_vibe = false;
    }

    if (true_key == CfgKeyCelsiusTemperature) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Received temperature in Celsius");
      #endif
      snprintf(temp_c_buffer, sizeof(temp_c_buffer), "%d°", (int)t->value->int32);
      //weather_needs_update = false;
      conf_vibe = false;
    }

    if (true_key == CfgKeyConditions) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Received conditions");
      #endif
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
      //weather_needs_update = false;
      conf_vibe = false;
    }

    if (true_key == CfgKeyWeatherError) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_ERROR, "Received weather error!");
      #endif

      if (language == 0) { // en
        snprintf(temp_buffer, sizeof(temp_buffer), "%s", "Error");
        snprintf(temp_c_buffer, sizeof(temp_c_buffer), "%s", "Error");
        snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", "City not found");
      } else if (language == 1) { // fr
        snprintf(temp_buffer, sizeof(temp_buffer), "%s", "Erreur");
        snprintf(temp_c_buffer, sizeof(temp_c_buffer), "%s", "Erreur");
        snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", "ville introuvable");
      } else if (language == 2) { // es
        snprintf(temp_buffer, sizeof(temp_buffer), "%s", "Error");
        snprintf(temp_c_buffer, sizeof(temp_c_buffer), "%s", "Error");
        snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", "hay tal ciudad");
      } else if (language == 3) { // de
        snprintf(temp_buffer, sizeof(temp_buffer), "%s", "Fehler");
        snprintf(temp_c_buffer, sizeof(temp_c_buffer), "%s", "Fehler");
        snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", "keine solche Stadt");
      }

      conf_vibe = false;
    }

    if (true_key == CfgKeyWeatherMode) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting weather_mode");
      #endif

      last_weather_mode = weather_mode;
      weather_mode = atoi(t->value->cstring);

      if (last_weather_mode == 2 && weather_mode == 0) { // If weather has hidden->shown
        weather_needs_update = true;
      }
    }

    if (true_key == CfgKeyUseCelsius) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting use_celsius");
      #endif

      use_celsius = t->value->int32;
    }

    if (true_key == CfgKeyWeatherLocation) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Received weather_location");
      #endif
    }

    if (true_key == CfgKeyLanguage) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting language");
      #endif

      last_language = language;
      language = atoi(t->value->cstring);

      if (language != last_language) {
        weather_needs_update = true;
      }
    }

    if (true_key == CfgKeyEuropeanDate) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting euro_date");
      #endif
      euro_date = t->value->int32;
    }

    if (true_key == CfgKeyVibeOnDisconnect) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting vibe_disconnect");
      #endif
      vibe_disconnect = t->value->int32;
    }

    if (true_key == CfgKeyVibeOnConnect) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting vibe_connect");
      #endif
      vibe_connect = t->value->int32;
    }

    if (true_key == CfgKeyBackgroundColour) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting background_colour");
      #endif
      background_colour = t->value->int32;
    }

    if (true_key == CfgKeyTextColour) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting text_colour");
      #endif
      text_colour = t->value->int32;
    }

    if (true_key == CfgKeyInvertColours) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting inv_colours");
      #endif
      inv_colours = t->value->int32;
    }

    if (true_key == CfgKeyShowSeconds) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting show_seconds");
      #endif
      show_seconds = t->value->int32;
    }

    if (true_key == CfgKeyMiddleBarMode) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting middle_bar_mode");
      #endif
      middle_bar_mode = atoi(t->value->cstring);
    }

    if (true_key == CfgKeyUseAutomaticStepGoal) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting auto_step_goal");
      #endif
      auto_step_goal = t->value->int32;
    }

    if (true_key == CfgKeyManualStepGoal) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting manual_step_goal");
      #endif
      manual_step_goal = t->value->int32;
    }

    if (true_key == CfgKeyUseNightMode) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting use_night_mode");
      #endif
      use_night_mode = t->value->int32;
    }

    if (true_key == CfgKeyNightModeStart) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting night_start_hour");
      #endif
      night_start_hour = atoi(t->value->cstring);
    }

    if (true_key == CfgKeyNightModeEnd) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting night_end_hour");
      #endif
      night_end_hour = atoi(t->value->cstring);
    }

    if (true_key == CfgKeyNightBackgroundColour) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting night_background_colour");
      #endif
      night_background_colour = t->value->int32;
    }

    if (true_key == CfgKeyNightTextColour) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Setting night_text_colour");
      #endif
      night_text_colour = t->value->int32;
    }

    t = dict_read_next(iter);
  }

  // All done receiving settings, vibrate to notify the user
  if (conf_vibe) vibes_double_pulse();

  // Then update everything that needs updating
  update_colours();
  update_time();
  size_time_layers();

  if (weather_needs_update) {
    update_weather();
  } else {
    display_weather();
  }

  layer_mark_dirty(middle_bar_layer);
}

void inbox_failed_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Incoming message dropped! - %d", reason);
}

void outbox_sent_handler(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

void outbox_failed_handler(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

void init_messaging() {
  app_message_register_inbox_received(inbox_recv_handler);
  app_message_register_inbox_dropped(inbox_failed_handler);
  app_message_register_outbox_sent(outbox_sent_handler);
  app_message_register_outbox_failed(outbox_failed_handler);
  app_message_open(256, 256);
}
