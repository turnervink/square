#pragma once

#include "middle_bar.h"

Window *main_window;
TextLayer *time_layer, *date_layer;
Layer *middle_bar_layer;

void update_time();
void main_window_push();
