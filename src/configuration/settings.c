#include <pebble.h>
#include "settings.h"
#include "../main_window.h"

#define STORED_SETTINGS 5555

void save_settings() {
  persist_write_bool(STORED_SETTINGS, true);

  for (int i = 0; i < CfgKeyCount; i++) {

    if (i == CfgKeyWeatherMode) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for weather_mode", weather_mode);
      persist_write_int(MESSAGE_KEY_CfgKeyWeatherMode, weather_mode);
    }

    if (i == CfgKeyWeatherLocation) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving fake value for weather_location");
      persist_write_int(MESSAGE_KEY_CfgKeyWeatherLocation, 0);
    }

    if (i == CfgKeyLanguage) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for language");
      persist_write_int(MESSAGE_KEY_CfgKeyLanguage, language);
    }

    if (i == CfgKeyEuropeanDate) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for euro_date");
      persist_write_int(MESSAGE_KEY_CfgKeyEuropeanDate, euro_date);
    }

    if (i == CfgKeyVibeOnDisconnect) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for vibe_disconnect");
      persist_write_int(MESSAGE_KEY_CfgKeyVibeOnDisconnect, vibe_disconnect);
    }

    if (i == CfgKeyVibeOnConnect) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for vibe_connect");
      persist_write_int(MESSAGE_KEY_CfgKeyVibeOnConnect, vibe_connect);
    }

    if (i == CfgKeyBackgroundColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for background_colour", background_colour);
      persist_write_int(MESSAGE_KEY_CfgKeyBackgroundColour, background_colour);
    }

    if (i == CfgKeyTextColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for text_colour", text_colour);
      persist_write_int(MESSAGE_KEY_CfgKeyTextColour, text_colour);
    }

    if (i == CfgKeyInvertColours) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for inv_colours");
      persist_write_int(MESSAGE_KEY_CfgKeyInvertColours, inv_colours);
    }

    if (i == CfgKeyShowSeconds) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for show_seconds");
      persist_write_int(MESSAGE_KEY_CfgKeyShowSeconds, show_seconds);
    }

    if (i == CfgKeyMiddleBarMode) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for middle_bar_mode");
      persist_write_int(MESSAGE_KEY_CfgKeyMiddleBarMode, middle_bar_mode);
    }

    if (i == CfgKeyUseAutomaticStepGoal) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for auto_step_goal");
      persist_write_int(MESSAGE_KEY_CfgKeyUseAutomaticStepGoal, auto_step_goal);
    }

    if (i == CfgKeyManualStepGoal) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for manual_step_goal");
      persist_write_int(MESSAGE_KEY_CfgKeyManualStepGoal, manual_step_goal);
    }

    if (i == CfgKeyUseNightMode) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for use_night_mode");
      persist_write_int(MESSAGE_KEY_CfgKeyUseNightMode, use_night_mode);
    }

    if (i == CfgKeyNightModeStart) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for night_start_hour");
      persist_write_int(MESSAGE_KEY_CfgKeyNightModeStart, night_start_hour);
    }

    if (i== CfgKeyNightModeEnd) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for night_end_hour");
      persist_write_int(MESSAGE_KEY_CfgKeyNightModeEnd, night_end_hour);
    }

    if (i == CfgKeyNightBackgroundColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for night_background_colour", night_background_colour);
      persist_write_int(MESSAGE_KEY_CfgKeyNightBackgroundColour, night_background_colour);
    }

    if (i == CfgKeyNightTextColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for night_text_colour", night_text_colour);
      persist_write_int(MESSAGE_KEY_CfgKeyNightTextColour, night_text_colour);
    }
  }
}

void load_settings() {
  if (!persist_exists(STORED_SETTINGS)) {
    // Set default settings
    APP_LOG(APP_LOG_LEVEL_INFO, "Setting default settings");

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
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for weather_mode", weather_mode);
      }

      if (i == CfgKeyLanguage) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for language");
        language = persist_read_int(MESSAGE_KEY_CfgKeyLanguage);
      }

      if (i == CfgKeyEuropeanDate) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for euro_date");
        euro_date = persist_read_int(MESSAGE_KEY_CfgKeyEuropeanDate);
      }

      if (i == CfgKeyVibeOnDisconnect) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for vibe_disconnect");
        vibe_disconnect = persist_read_int(MESSAGE_KEY_CfgKeyVibeOnDisconnect);
      }

      if (i == CfgKeyVibeOnConnect) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for vibe_connect");
        vibe_connect = persist_read_int(MESSAGE_KEY_CfgKeyVibeOnConnect);
      }

      if (i == CfgKeyBackgroundColour) {
        background_colour = persist_read_int(MESSAGE_KEY_CfgKeyBackgroundColour);
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for background_colour", background_colour);
      }

      if (i == CfgKeyTextColour) {
        text_colour = persist_read_int(MESSAGE_KEY_CfgKeyTextColour);
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored of %d value for text_colour", text_colour);
      }

      if (i == CfgKeyInvertColours) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for inv_colours");
        inv_colours = persist_read_int(MESSAGE_KEY_CfgKeyInvertColours);
      }

      if (i == CfgKeyShowSeconds) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for show_seconds");
        show_seconds = persist_read_int(MESSAGE_KEY_CfgKeyShowSeconds);
      }

      if (i == CfgKeyMiddleBarMode) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for middle_bar_mode");
        middle_bar_mode = persist_read_int(MESSAGE_KEY_CfgKeyMiddleBarMode);
      }

      if (i == CfgKeyUseAutomaticStepGoal) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for auto_step_goal");
        auto_step_goal = persist_read_int(MESSAGE_KEY_CfgKeyUseAutomaticStepGoal);
      }

      if (i == CfgKeyManualStepGoal) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for manual_step_goal");
        manual_step_goal = persist_read_int(MESSAGE_KEY_CfgKeyManualStepGoal);
      }

      if (i == CfgKeyUseNightMode) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for use_night_mode");
        use_night_mode = persist_read_int(MESSAGE_KEY_CfgKeyUseNightMode);
      }

      if (i == CfgKeyNightModeStart) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for night_start_hour");
        night_start_hour = persist_read_int(MESSAGE_KEY_CfgKeyNightModeStart);
      }

      if (i == CfgKeyNightModeEnd) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for night_end_hour");
        night_end_hour = persist_read_int(MESSAGE_KEY_CfgKeyNightModeEnd);
      }

      if (i == CfgKeyNightBackgroundColour) {
        night_background_colour = persist_read_int(MESSAGE_KEY_CfgKeyNightBackgroundColour);
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for night_background_colour", night_background_colour);
      }

      if (i == CfgKeyNightTextColour) {
        night_text_colour = persist_read_int(MESSAGE_KEY_CfgKeyNightTextColour);
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for night_text_colour", night_text_colour);
      }
    }
  }
}
