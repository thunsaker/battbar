// 2013 Thomas Hunsaker @thunsaker
// BattBar.c
// BattBar v.1.2

#include <pebble.h>
#include "battbar.h"

static BitmapLayer *image_layer_battery;
static GBitmap *image_line;
static BBOptions options;
static Layer *current_window;

void battbar(void) {
	options.position = BATTBAR_POSITION_LEFT;
	options.direction = BATTBAR_DIRECTION_UP;
	options.color = BATTBAR_COLOR_BLACK;
	options.isWatchApp = false;
}

static void battbar_handle_battery(BatteryChargeState charge_state) {
	DrawBattBar(charge_state);
}

void SetupBattBar(BBOptions myOptions, Layer *myWindow) {
	options = myOptions;
	current_window = myWindow;
	battery_state_service_subscribe(&battbar_handle_battery);
}

void DrawBattBar() {
	BatteryChargeState charge_state = battery_state_service_peek();
	RefreshBattBar(charge_state);
}

void RefreshBattBar(BatteryChargeState charge_state) {
	int height = 168; // Without Title Bar
	int width = 144;
	int bar_size = 2;
	double segment = 1.86; //1.6;
	if(options.isWatchApp) {
		height = 152; // With Title Bar
		segment = 1.68; // 1.5;
	}
	
	uint8_t raw_percent = charge_state.charge_percent;
	uint8_t percent_display = raw_percent * segment;
	bool isCharging = charge_state.is_charging;
	
	if(options.position == BATTBAR_POSITION_BOTTOM || options.position == BATTBAR_POSITION_TOP) {
		segment = 1.6; // 1.4;
		percent_display = raw_percent * segment;
		if(isCharging) {
			image_line = gbitmap_create_with_resource(RESOURCE_ID_CHARGING_LINE_LONG);
		} else {
			if(options.color == BATTBAR_COLOR_BLACK) {
				image_line = gbitmap_create_with_resource(RESOURCE_ID_BLACK_LINE_LONG);
			} else {
				image_line = gbitmap_create_with_resource(RESOURCE_ID_WHITE_LINE_LONG);
			}
		}
			
		if(options.position == BATTBAR_POSITION_TOP) {
			image_layer_battery = bitmap_layer_create(GRect(0,0,percent_display,bar_size));
		} else {
			image_layer_battery = bitmap_layer_create(GRect(0,height-bar_size,percent_display,bar_size));
		}
	} else {
		if(isCharging) {
			image_line = gbitmap_create_with_resource(RESOURCE_ID_CHARGING_LINE_FULL);
		} else {
			if(options.color == BATTBAR_COLOR_BLACK) {
				image_line = gbitmap_create_with_resource(RESOURCE_ID_BLACK_LINE_FULL);
			} else {
				image_line = gbitmap_create_with_resource(RESOURCE_ID_WHITE_LINE_FULL);
			}
		}

		if(options.position == BATTBAR_POSITION_LEFT) {
			if(options.direction == BATTBAR_DIRECTION_UP) {
				image_layer_battery = bitmap_layer_create(GRect(0,0,bar_size,percent_display));
			} else {
				image_layer_battery = bitmap_layer_create(GRect(0,height-percent_display,bar_size,percent_display));
			}
		} else if (options.position == BATTBAR_POSITION_RIGHT) {
			if(options.direction == BATTBAR_DIRECTION_UP) {
				image_layer_battery = bitmap_layer_create(GRect(width-bar_size,0,bar_size,percent_display));
			} else {
				image_layer_battery = bitmap_layer_create(GRect(width-bar_size,height-percent_display,bar_size,percent_display));
			}
		}
	}
	
	bitmap_layer_set_bitmap(image_layer_battery, image_line);
	layer_add_child(current_window, bitmap_layer_get_layer(image_layer_battery));
}