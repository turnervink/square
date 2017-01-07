#include <pebble.h>
#include "main_window.h"
#include "configuration/messaging.h"
#include "configuration/settings.h"
#include "middle_bar.h"
#include "weather/weather.h"
#include "bluetooth/bluetooth.h"
#include "colours.h"

void get_launch_minute() {
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);

  launch_minute = tick_time->tm_min;
  APP_LOG(APP_LOG_LEVEL_INFO, "Launch minute is %d", launch_minute);
}

static const uint32_t const segments[] = {200, 100, 200, 100, 200};
VibePattern hour_chime = {
  .durations = segments,
  .num_segments = ARRAY_LENGTH(segments),
};

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();

  if (tick_time->tm_min == 0 && tick_time->tm_sec == 0) {
    if (hourly_vibe == 1 && quiet_time_is_active() == false) {
      vibes_enqueue_custom_pattern(hour_chime);
    }
  }

  if (tick_time->tm_min == launch_minute && tick_time->tm_sec == 0) {
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
  get_launch_minute();
}

static void deinit() {
  save_settings();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
