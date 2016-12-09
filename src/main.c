#include <pebble.h>
#include "main_window.h"
#include "configuration/messaging.h"
#include "configuration/settings.h"
#include "middle_bar.h"
#include "weather/weather.h"
#include "bluetooth/bluetooth.h"
#include "colours.h"

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();

  if (tick_time->tm_min == 0) {
    if (hourly_vibe == 1 && quiet_time_is_active() == false) {
      vibes_short_pulse();
    }
  }

  if (tick_time->tm_min % 30 == 0 && tick_time->tm_sec == 0) {
    update_weather();
  }

  if (tick_time->tm_hour == night_start_hour && tick_time->tm_min == 0) {
    update_colours();
  }

  if (tick_time->tm_hour == night_end_hour && tick_time->tm_min == 0){
    update_colours();
  }
}

static void init() {
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
  battery_state_service_subscribe(battery_handler);
  bluetooth_connection_service_subscribe(bluetooth_handler);
  accel_tap_service_subscribe(accel_handler);


  init_messaging();

  main_window_push();
}

static void deinit() {
  save_settings();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
