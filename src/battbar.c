// 2013 Thomas Hunsaker @thunsaker

#include <pebble.h>
#include "battbar.h"

static BitmapLayer *image_layer_battery;
static GBitmap *image_line;

void drawBatteryBar(const BBPosition position, const BBDirection direction, const BBColor color, uint8_t percentage, Layer *current_window) {
	uint8_t percent_display = percentage * 1.5;
	if(position == BATBAR_POSITION_BOTTOM) {
		percent_display = percentage * 1.4;
		image_layer_battery = bitmap_layer_create(GRect(0,148,percent_display,4));
		image_line = gbitmap_create_with_resource(RESOURCE_ID_BLACK_LINE_LONG);
	} else {
		image_line = gbitmap_create_with_resource(RESOURCE_ID_BLACK_LINE_FULL);
		if(position == BATBAR_POSITION_LEFT) {
			if(direction == BATBAR_DIRECTION_UP) {
				image_layer_battery = bitmap_layer_create(GRect(0,0,4,percent_display));
			} else {
				image_layer_battery = bitmap_layer_create(GRect(0,percent_display,4,152-percent_display));
			}
		} else if (position == BATBAR_POSITION_RIGHT) {
			if(direction == BATBAR_DIRECTION_UP) {
				image_layer_battery = bitmap_layer_create(GRect(140,0,4,percent_display));
			} else {
				image_layer_battery = bitmap_layer_create(GRect(140,percent_display,4,152-percent_display));
			}
		}
	}
	
	bitmap_layer_set_bitmap(image_layer_battery, image_line);
	layer_add_child(current_window, bitmap_layer_get_layer(image_layer_battery));
}