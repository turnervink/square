#pragma once

void battery_handler(BatteryChargeState state);
void health_handler(HealthEventType event, void *context);
void middle_bar_update_proc(Layer *layer, GContext *ctx);
