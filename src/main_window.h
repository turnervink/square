#pragma once

Window *main_window;
TextLayer *time_layer, *date_layer, *temperature_layer, *conditions_layer;
Layer *middle_bar_layer;

void update_time();
void main_window_push();
