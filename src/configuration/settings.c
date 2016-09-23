#include <pebble.h>
#include "settings.h"
#include "../main_window.h"
#include "../logs.h"

#define STORED_SETTINGS 5555

void save_settings() {
  persist_write_bool(STORED_SETTINGS, true);

  for (int i = 0; i < CfgKeyCount; i++) {

    if (i == CfgKeyWeatherMode) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for weather_mode", weather_mode);
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyWeatherMode, weather_mode);
    }

    if (i == CfgKeyWeatherLocation) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving fake value for weather_location");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyWeatherLocation, 0);
    }

    if (i == CfgKeyLanguage) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for language");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyLanguage, language);
    }

    if (i == CfgKeyEuropeanDate) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for euro_date");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyEuropeanDate, euro_date);
    }

    if (i == CfgKeyVibeOnDisconnect) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for vibe_disconnect");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyVibeOnDisconnect, vibe_disconnect);
    }

    if (i == CfgKeyVibeOnConnect) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for vibe_connect");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyVibeOnConnect, vibe_connect);
    }

    if (i == CfgKeyBackgroundColour) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for background_colour", background_colour);
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyBackgroundColour, background_colour);
    }

    if (i == CfgKeyTextColour) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for text_colour", text_colour);
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyTextColour, text_colour);
    }

    if (i == CfgKeyInvertColours) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for inv_colours");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyInvertColours, inv_colours);
    }

    if (i == CfgKeyShowSeconds) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for show_seconds");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyShowSeconds, show_seconds);
    }

    if (i == CfgKeyMiddleBarMode) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for middle_bar_mode");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyMiddleBarMode, middle_bar_mode);
    }

    if (i == CfgKeyUseAutomaticStepGoal) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for auto_step_goal");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyUseAutomaticStepGoal, auto_step_goal);
    }

    if (i == CfgKeyManualStepGoal) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for manual_step_goal");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyManualStepGoal, manual_step_goal);
    }

    if (i == CfgKeyUseNightMode) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for use_night_mode");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyUseNightMode, use_night_mode);
    }

    if (i == CfgKeyNightModeStart) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for night_start_hour");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyNightModeStart, night_start_hour);
    }

    if (i== CfgKeyNightModeEnd) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for night_end_hour");
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyNightModeEnd, night_end_hour);
    }

    if (i == CfgKeyNightBackgroundColour) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for night_background_colour", night_background_colour);
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyNightBackgroundColour, night_background_colour);
    }

    if (i == CfgKeyNightTextColour) {
      #ifdef DEBUG_MODE
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for night_text_colour", night_text_colour);
      #endif
      persist_write_int(MESSAGE_KEY_CfgKeyNightTextColour, night_text_colour);
    }
  }
}

void load_settings() {
  if (!persist_exists(STORED_SETTINGS)) {
    // Set default settings
    APP_LOG(APP_LOG_LEVEL_WARNING, "No saved settings, setting defaults");

    weather_mode = 0;
    language = 0;
    euro_date = 0;
    vibe_disconnect = 1;
    vibe_connect = 1;
    background_colour = 0x000000;
    text_colour = 0x00ff00;
    inv_colours = 0;
    show_seconds = 0;
    middle_bar_mode = 1;
    auto_step_goal = 1;
    use_night_mode = 0;
    night_start_hour = 20;
    night_end_hour = 7;
    night_background_colour = 0x000000;
    night_text_colour = 0xFFFFFF;
  } else {
    // Load stored settings
    APP_LOG(APP_LOG_LEVEL_INFO, "Loading saved settings");

    for (int i = 0; i < CfgKeyCount; i++) {

      if (i== CfgKeyWeatherMode) {
        weather_mode = persist_read_int(MESSAGE_KEY_CfgKeyWeatherMode);
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for weather_mode", weather_mode);
        #endif
      }

      if (i == CfgKeyLanguage) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for language");
        #endif
        language = persist_read_int(MESSAGE_KEY_CfgKeyLanguage);
      }

      if (i == CfgKeyEuropeanDate) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for euro_date");
        #endif
        euro_date = persist_read_int(MESSAGE_KEY_CfgKeyEuropeanDate);
      }

      if (i == CfgKeyVibeOnDisconnect) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for vibe_disconnect");
        #endif
        vibe_disconnect = persist_read_int(MESSAGE_KEY_CfgKeyVibeOnDisconnect);
      }

      if (i == CfgKeyVibeOnConnect) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for vibe_connect");
        #endif
        vibe_connect = persist_read_int(MESSAGE_KEY_CfgKeyVibeOnConnect);
      }

      if (i == CfgKeyBackgroundColour) {
        background_colour = persist_read_int(MESSAGE_KEY_CfgKeyBackgroundColour);
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for background_colour", background_colour);
        #endif
      }

      if (i == CfgKeyTextColour) {
        text_colour = persist_read_int(MESSAGE_KEY_CfgKeyTextColour);
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored of %d value for text_colour", text_colour);
        #endif
      }

      if (i == CfgKeyInvertColours) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for inv_colours");
        #endif
        inv_colours = persist_read_int(MESSAGE_KEY_CfgKeyInvertColours);
      }

      if (i == CfgKeyShowSeconds) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for show_seconds");
        #endif
        show_seconds = persist_read_int(MESSAGE_KEY_CfgKeyShowSeconds);
      }

      if (i == CfgKeyMiddleBarMode) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for middle_bar_mode");
        #endif
        middle_bar_mode = persist_read_int(MESSAGE_KEY_CfgKeyMiddleBarMode);
      }

      if (i == CfgKeyUseAutomaticStepGoal) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for auto_step_goal");
        #endif
        auto_step_goal = persist_read_int(MESSAGE_KEY_CfgKeyUseAutomaticStepGoal);
      }

      if (i == CfgKeyManualStepGoal) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for manual_step_goal");
        #endif
        manual_step_goal = persist_read_int(MESSAGE_KEY_CfgKeyManualStepGoal);
      }

      if (i == CfgKeyUseNightMode) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for use_night_mode");
        #endif
        use_night_mode = persist_read_int(MESSAGE_KEY_CfgKeyUseNightMode);
      }

      if (i == CfgKeyNightModeStart) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for night_start_hour");
        #endif
        night_start_hour = persist_read_int(MESSAGE_KEY_CfgKeyNightModeStart);
      }

      if (i == CfgKeyNightModeEnd) {
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for night_end_hour");
        #endif
        night_end_hour = persist_read_int(MESSAGE_KEY_CfgKeyNightModeEnd);
      }

      if (i == CfgKeyNightBackgroundColour) {
        night_background_colour = persist_read_int(MESSAGE_KEY_CfgKeyNightBackgroundColour);
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for night_background_colour", night_background_colour);
        #endif
      }

      if (i == CfgKeyNightTextColour) {
        night_text_colour = persist_read_int(MESSAGE_KEY_CfgKeyNightTextColour);
        #ifdef DEBUG_MODE
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for night_text_colour", night_text_colour);
        #endif
      }
    }
  }
}
