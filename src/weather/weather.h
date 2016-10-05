#pragma once

char temp_buffer[15];
char temp_c_buffer[15];
char conditions_buffer[100];

void accel_handler(AccelAxisType axis, int32_t direction);
void update_weather();
void size_weather();
void display_weather();
void size_weather_layers();
