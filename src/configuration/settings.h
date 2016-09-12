#pragma once

#include "../colours.h"

typedef enum {
  // Numbered items are exceptions (non-bool)
  CfgKeyTemperature,
  CfgKeyCelsiusTemperature,
  CfgKeyConditions,
  CfgKeyWeatherMode, // 3
  CfgKeyWeatherLocation, // 4
  CfgKeyLanguage, // 5
  CfgKeyEuropeanDate,
  CfgKeyBackgroundColour,  // 7
  CfgKeyTextColour, // 8
  CfgKeyInvertColours,
  CfgKeyMiddleBarMode, // 10
  CfgKeyUseAutomaticStepGoal,
  CfgKeyManualStepGoal, // 12
  CfgKeyUseNightMode,
  CfgKeyNightModeStart, // 14
  CfgKeyNightModeEnd, // 15
  CfgKeyNightBackgroundColour,  // 16
  CfgKeyNightTextColour,  // 17


  CfgKeyCount,
} CfgKey;

// Define ints for non-bool settings
int background_colour, text_colour, night_background_colour, night_text_colour;
int night_start_hour, night_end_hour;
int last_language, language;
int middle_bar_mode;
int manual_step_goal;
int last_weather_mode, weather_mode;

int euro_date, inv_colours, auto_step_goal, use_night_mode;

void parse_settings(int key, bool value);
bool get_settings(int key);
void save_settings();
void load_settings();
