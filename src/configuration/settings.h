#pragma once

#include "../colours.h"

typedef enum {
  // Numbered items are exceptions (non-bool)
  CfgKeyTemperature,
  CfgKeyCelsiusTemperature,
  CfgKeyConditions,
  CfgKeyWeatherMode, // 3
  CfgKeyLanguage, // 4
  CfgKeyEuropeanDate,
  CfgKeyBackgroundColour,  // 6
  CfgKeyTextColour, // 7
  CfgKeyInvertColours,
  CfgKeyMiddleBarMode, // 9
  CfgKeyUseAutomaticStepGoal,
  CfgKeyManualStepGoal, // 11
  CfgKeyUseNightMode,
  CfgKeyNightModeStart, // 13
  CfgKeyNightModeEnd, // 14
  CfgKeyNightBackgroundColour,  // 15
  CfgKeyNightTextColour,  // 16


  CfgKeyCount,
} CfgKey;

// Define ints for non-bool settings
int background_colour, text_colour, night_background_colour, night_text_colour;
int night_start_hour, night_end_hour;
int last_language, language;
int middle_bar_mode;
int manual_step_goal;
int weather_mode;

void parse_settings(int key, bool value);
bool get_settings(int key);
void save_settings();
void load_settings();
