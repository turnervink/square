#pragma once

Window *main_window;
TextLayer *time_layer, *date_layer, *temperature_layer, *conditions_layer, *top_bt_layer, *btm_bt_layer;
Layer *middle_bar_layer;

void size_time_layers();
void update_time();
void main_window_push();
