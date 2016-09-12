#include <pebble.h>
#include "main_window.h"
#include "middle_bar.h"
#include "configuration/settings.h"

int steps, steps_average;

void battery_handler(BatteryChargeState state) {
  if (middle_bar_mode == 1) {
    layer_mark_dirty(middle_bar_layer);
  }
}

#ifdef PBL_HEALTH
void health_handler(HealthEventType event, void *context) {
	time_t start = time_start_of_today();
	time_t end = time(NULL);
	time_t end_of_day = time_start_of_today() + SECONDS_PER_DAY;
	HealthServiceAccessibilityMask mask = health_service_metric_accessible(HealthMetricStepCount, start, end);

	if (mask & HealthServiceAccessibilityMaskAvailable) {
		APP_LOG(APP_LOG_LEVEL_INFO, "Step data available!");
		steps = health_service_sum_today(HealthMetricStepCount);
    steps_average = health_service_sum_averaged(HealthMetricStepCount, start, end_of_day, HealthServiceTimeScopeDailyWeekdayOrWeekend);
	} else {
		APP_LOG(APP_LOG_LEVEL_INFO, "Step data unavailable");
	}
}
#endif

void middle_bar_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(window_get_root_layer(main_window));

  // Pick the correct colour based on night mode/invert setting
  #ifdef PBL_COLOR
  if (in_night_range()) {
    graphics_context_set_fill_color(ctx, GColorFromHEX(night_text_colour));
  } else {
    graphics_context_set_fill_color(ctx, GColorFromHEX(text_colour));
  }
  #else
  if (inv_colours == 1) {
    graphics_context_set_fill_color(ctx, GColorBlack);
  } else {
    graphics_context_set_fill_color(ctx, GColorWhite);
  }
  #endif

  // Draw the right type of bar based on mode setting
  if (middle_bar_mode == 0) {
    // Draw static bar
    APP_LOG(APP_LOG_LEVEL_INFO, "Bar mode 0");

    graphics_fill_rect(ctx, GRect(PBL_IF_ROUND_ELSE(20, 2), (bounds.size.h / 2) + 8, 140, 2), 0, GCornerNone); // Draw static bar
  } else if (middle_bar_mode == 1) {
    // Draw battery bars shrinking from either side of the screen for that cool "middle out" effect
    APP_LOG(APP_LOG_LEVEL_INFO, "Bar mode 1");

    BatteryChargeState state = battery_state_service_peek();
		int pct = state.charge_percent;

    APP_LOG(APP_LOG_LEVEL_INFO, "Current battery pct is %d", pct);

    graphics_fill_rect(ctx, GRect((bounds.size.w / 2), (bounds.size.h / 2) + 8, ((140)-(((100-pct)/10)*14))/2, 2), 0, GCornerNone); // Centre to right
		graphics_fill_rect(ctx, GRect((bounds.size.w / 2), (bounds.size.h / 2) + 8, -((140)-(((100-pct)/10)*14))/2, 2), 0, GCornerNone); // Centre to left
  } else if (middle_bar_mode == 2) {
    #ifdef PBL_HEALTH
    // Draw step goal progress bar
    APP_LOG(APP_LOG_LEVEL_INFO, "Bar mode 2");

    int px_per_step_manual = manual_step_goal / 140; // Divide goal by full bar width
    int px_per_step_auto = steps_average / 140;

    if (auto_step_goal == 1) {
      graphics_fill_rect(ctx, GRect(PBL_IF_ROUND_ELSE(20, 2), (bounds.size.h / 2) + 8, steps / px_per_step_auto, 2), 0, GCornerNone); // Draw steps bar
    } else {
      graphics_fill_rect(ctx, GRect(PBL_IF_ROUND_ELSE(20, 2), (bounds.size.h / 2) + 8, steps / px_per_step_manual, 2), 0, GCornerNone); // Draw steps bar
    }
    #else
    // If the watch doesn't support Pebble Health, just show the static bar
    graphics_fill_rect(ctx, GRect(PBL_IF_ROUND_ELSE(20, 2), (bounds.size.h / 2) + 8, 140, 2), 0, GCornerNone); // Draw static bar
    #endif
  } else {
    // Draw static bar again, just in case we get a weird value for some reason
    APP_LOG(APP_LOG_LEVEL_INFO, "Bar mode else");

    graphics_fill_rect(ctx, GRect(PBL_IF_ROUND_ELSE(20, 2), (bounds.size.h / 2) + 8, 140, 2), 0, GCornerNone); // Draw static bar
  }

}
