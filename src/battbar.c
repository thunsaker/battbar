// 2013 Thomas Hunsaker @thunsaker
// BattBar.c
// BattBar v.1.1

#include <pebble.h>
#include "battbar.h"

static BitmapLayer *image_layer_battery;
static GBitmap *image_line;

void DrawBattBar(BBOptions options, Layer *current_window) {
	int height = 168; // Without Title Bar
	int width = 144;
	double segment = 1.6;
	if(options.isWatchApp) {
		height = 152; // With Title Bar
		segment = 1.5;
	}
	
	BatteryChargeState charge_state = battery_state_service_peek();
	uint8_t raw_percent = charge_state.charge_percent;
	uint8_t percent_display = raw_percent * segment;
	
	if(options.position == BATTBAR_POSITION_BOTTOM || options.position == BATTBAR_POSITION_TOP) {
		segment = 1.4;
		percent_display = raw_percent * segment;
		
		if(options.color == BATTBAR_COLOR_BLACK) {
			image_line = gbitmap_create_with_resource(RESOURCE_ID_BLACK_LINE_LONG);
		} else {
			image_line = gbitmap_create_with_resource(RESOURCE_ID_WHITE_LINE_LONG);
		}
			
		if(options.position == BATTBAR_POSITION_TOP) {
			image_layer_battery = bitmap_layer_create(GRect(0,0,percent_display,4));
		} else {
			image_layer_battery = bitmap_layer_create(GRect(0,height-4,percent_display,4));
		}
	} else {
		if(options.color == BATTBAR_COLOR_BLACK) {
			image_line = gbitmap_create_with_resource(RESOURCE_ID_BLACK_LINE_FULL);
		} else {
			image_line = gbitmap_create_with_resource(RESOURCE_ID_WHITE_LINE_FULL);
		}

		if(options.position == BATTBAR_POSITION_LEFT) {
			if(options.direction == BATTBAR_DIRECTION_UP) {
				image_layer_battery = bitmap_layer_create(GRect(0,0,4,percent_display));
			} else {
				image_layer_battery = bitmap_layer_create(GRect(0,height-percent_display,4,percent_display));
			}
		} else if (options.position == BATTBAR_POSITION_RIGHT) {
			if(options.direction == BATTBAR_DIRECTION_UP) {
				image_layer_battery = bitmap_layer_create(GRect(width-4,0,4,percent_display));
			} else {
				image_layer_battery = bitmap_layer_create(GRect(width-4,height-percent_display,4,percent_display));
			}
		}
	}
	
	bitmap_layer_set_bitmap(image_layer_battery, image_line);
	layer_add_child(current_window, bitmap_layer_get_layer(image_layer_battery));
}