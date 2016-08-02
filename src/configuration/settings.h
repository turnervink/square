#pragma once

#include "../colours.h"

typedef enum {
  // Numbered items are exceptions (non-bool)
  CfgKeyTemperature, // 0
  CfgKeyCelsiusTemperature, // 1
  CfgKeyConditions, // 2
  CfgKeyLanguage, // 3
  CfgKeyEuropeanDate,
  CfgKeyBackgroundColour,  // 5
  CfgKeyTextColour, // 6
  CfgKeyInvertColours,
  CfgKeyMiddleBarMode, // 8
  CfgKeyUseAutomaticStepGoal,
  CfgKeyManualStepGoal, // 10
  CfgKeyUseNightMode,
  CfgKeyNightModeStart, // 12
  CfgKeyNightModeEnd, // 13
  CfgKeyNightBackgroundColour,  // 14
  CfgKeyNightTextColour,  // 15

  CfgKeyCount,
} CfgKey;

// Define ints for non-bool settings
int background_colour, text_colour, night_background_colour, night_text_colour;
int night_start_hour, night_end_hour;
int language;
int middle_bar_mode;
int manual_step_goal;

void parse_settings(int key, bool value);
bool get_settings(int key);
void save_settings();
void load_settings();
