#pragma once

#include "../colours.h"

typedef enum {
  CfgKeyTemperature,
  CfgKeyCelsiusTemperature,
  CfgKeyConditions,
  CfgKeyWeatherMode,
  CfgKeyWeatherLocation,
  CfgKeyLanguage,
  CfgKeyEuropeanDate,
  CfgKeyVibeOnDisconnect,
  CfgKeyVibeOnConnect,
  CfgKeyBackgroundColour,
  CfgKeyTextColour,
  CfgKeyInvertColours,
  CfgKeyShowSeconds,
  CfgKeyMiddleBarMode,
  CfgKeyUseAutomaticStepGoal,
  CfgKeyManualStepGoal,
  CfgKeyUseNightMode,
  CfgKeyNightModeStart,
  CfgKeyNightModeEnd,
  CfgKeyNightBackgroundColour,
  CfgKeyNightTextColour,


  CfgKeyCount,
} CfgKey;

// Define ints for non-bool settings
int background_colour, text_colour, night_background_colour, night_text_colour;
int night_start_hour, night_end_hour;
int last_language, language;
int middle_bar_mode;
int manual_step_goal;
int last_weather_mode, weather_mode;

int euro_date, inv_colours, auto_step_goal, use_night_mode, vibe_disconnect, vibe_connect, show_seconds;

void parse_settings(int key, bool value);
bool get_settings(int key);
void save_settings();
void load_settings();
