#include <pebble.h>
#include "settings.h"
#include "../main_window.h"

// Thanks to Chris Lewis for hosting his watchface "Thin" on GitHub so I could use it for this config setup!

#define STORED_SETTINGS 5555

static bool config_settings[CfgKeyCount];

static int config_exceptions[9] = {
  3,
  5,
  6,
  8,
  10,
  12,
  13,
  14,
  15
};

static int weather_keys[3] = {
  0,
  1,
  2
};

bool is_exception(int key) {
  int arr_size = sizeof(config_exceptions) / sizeof(config_exceptions[0]);

  for (int i = 0; i < arr_size; i++) {
    if (config_exceptions[i] == key)
      return true;
  }

    return false;

}

bool is_weather(int key) {
  int arr_size = sizeof(weather_keys) / sizeof(weather_keys[0]);

  for (int i = 0; i < arr_size; i++) {
    if (weather_keys[i] == key)
      return true;
  }

    return false;

}

void parse_settings(int key, bool value) {

  if (is_exception(key)) { // If we have a non-bool key, we write a value of 1 to the config array
    APP_LOG(APP_LOG_LEVEL_INFO, "Key %d is an exception; adding a value to config array", key);
    config_settings[key] = 1;
  } else if (is_weather(key)) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Key %d is a weather key, ignoring", key);
  } else {
    APP_LOG(APP_LOG_LEVEL_INFO, "Parsing key %d that has a value of %d", key, value);
    config_settings[key] = value;
  }

}

bool get_settings(int key) {
  return config_settings[key];
}

void save_settings() {
  persist_write_bool(STORED_SETTINGS, true);

  for (int i = 0; i < CfgKeyCount; i++) {
    /* Save each config option, with exceptions for non-bool values
    NOTE: We still save every array element even if it's non-bool to keep the count correct */

    if (i == CfgKeyLanguage) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for language");
      persist_write_int(MESSAGE_KEY_CfgKeyLanguage, language);
    }

    if (i == CfgKeyTextColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for text_colour", text_colour);
      persist_write_int(MESSAGE_KEY_CfgKeyTextColour, text_colour);
    }

    if (i == CfgKeyMiddleBarMode) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for middle_bar_mode");
      persist_write_int(MESSAGE_KEY_CfgKeyMiddleBarMode, middle_bar_mode);
    }

    if (i == CfgKeyBackgroundColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for background_colour", background_colour);
      persist_write_int(MESSAGE_KEY_CfgKeyBackgroundColour, background_colour);
    }

    if (i == CfgKeyManualStepGoal) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for manual_step_goal");
      persist_write_int(MESSAGE_KEY_CfgKeyManualStepGoal, manual_step_goal);
    }

    if (i == CfgKeyNightModeStart) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for night_start_hour");
      persist_write_int(MESSAGE_KEY_CfgKeyNightModeStart, night_start_hour);
    }

    if (i== CfgKeyNightModeEnd) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value for night_end_hour");
      persist_write_int(MESSAGE_KEY_CfgKeyNightModeEnd, night_end_hour);
    }

    // Don't show we're saving the dummy array elements in the logs
    if (!is_exception(i)) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving setting %d with value of %d", i, config_settings[i]);
    }

    if (i == CfgKeyNightTextColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for night_text_colour", night_text_colour);
      persist_write_int(MESSAGE_KEY_CfgKeyNightTextColour, night_text_colour);
    }

    if (i == CfgKeyNightBackgroundColour) {
      APP_LOG(APP_LOG_LEVEL_INFO, "Saving value of %d for night_background_colour", night_background_colour);
      persist_write_int(MESSAGE_KEY_CfgKeyNightBackgroundColour, night_background_colour);
    }

    // Save bool options
    persist_write_bool(i, config_settings[i]);
  }
}

void load_settings() {
  if (!persist_exists(STORED_SETTINGS)) {
    // Set default settings
    APP_LOG(APP_LOG_LEVEL_INFO, "Setting default settings");

    language = 0;
    background_colour = 0x000000;
    text_colour = 0x00ff00;
    middle_bar_mode = 1;
    config_settings[CfgKeyInvertColours] = 0;
    config_settings[CfgKeyUseNightMode] = 0;
    night_start_hour = 20;
    night_end_hour = 7;
    night_background_colour = 0x000000;
    night_text_colour = 0xFFFFFF;
  } else {
    // Load stored settings
    APP_LOG(APP_LOG_LEVEL_INFO, "Loading saved settings");

    for (int i = 0; i < CfgKeyCount; i++) {

      // Load exceptions first
      if (i == CfgKeyLanguage) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loading stored value for language");
        language = persist_read_int(MESSAGE_KEY_CfgKeyLanguage);
      }

      if (i == CfgKeyTextColour) {

        text_colour = persist_read_int(MESSAGE_KEY_CfgKeyTextColour);
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored of %d value for text_colour", text_colour);
      }

      if (i == CfgKeyMiddleBarMode) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for middle_bar_mode");
        middle_bar_mode = persist_read_int(MESSAGE_KEY_CfgKeyMiddleBarMode);
      }

      if (i == CfgKeyBackgroundColour) {

        background_colour = persist_read_int(MESSAGE_KEY_CfgKeyBackgroundColour);
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for background_colour", background_colour);
      }

      if (i == CfgKeyManualStepGoal) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for manual_step_goal");
        manual_step_goal = persist_read_int(MESSAGE_KEY_CfgKeyManualStepGoal);
      }

      if (i == CfgKeyNightModeStart) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for night_start_hour");
        night_start_hour = persist_read_int(MESSAGE_KEY_CfgKeyNightModeStart);
      }

      if (i == CfgKeyNightModeEnd) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value for night_end_hour");
        night_end_hour = persist_read_int(MESSAGE_KEY_CfgKeyNightModeEnd);
      }

      if (i == CfgKeyNightTextColour) {

        night_text_colour = persist_read_int(MESSAGE_KEY_CfgKeyNightTextColour);
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for night_text_colour", night_text_colour);
      }

      if (i == CfgKeyNightBackgroundColour) {

        night_background_colour = persist_read_int(MESSAGE_KEY_CfgKeyNightBackgroundColour);
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded stored value of %d for night_background_colour", night_background_colour);
      }

      // Then load bool options
      config_settings[i] = persist_read_bool(i);

      // Don't show we're loading the stored dummy array elements in the logs
      if (!is_exception(i)) {
        APP_LOG(APP_LOG_LEVEL_INFO, "Loaded setting %d with value of %d", i, persist_read_bool(i));
      }
    }
  }
}
