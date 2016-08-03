#include <pebble.h>
#include "../main_window.h"

char temp_buffer[15];
char temp_c_buffer[15];
char conditions_buffer[100];
// TODO Size these buffers properly

void update_weather() {

}

void display_weather() {
  text_layer_set_text(temperature_layer, temp_c_buffer);
  text_layer_set_text(conditions_layer, conditions_buffer);
}
