#include "pebble.h"

static Window *window;

static TextLayer *text_layer_label;
static TextLayer *text_layer_percentage;
static BitmapLayer *image_layer_battery;
static GBitmap *image_line;

typedef enum {
	BATBAR_POSITION_LEFT,
	BATBAR_POSITION_RIGHT,
	BATBAR_POSITION_BOTTOM
} BBPosition;

typedef enum  {
	BATBAR_DIRECTION_UP,
	BATBAR_DIRECTION_DOWN
} BBDirection;

typedef enum {
	BATBAR_COLOR_BLACK,
	BATBAR_COLOR_WHITE
} BBColor;

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
	
	//image_layer_battery = bitmap_layer_create(GRect(0,0,4, percent_display));
	bitmap_layer_set_bitmap(image_layer_battery, image_line);
	layer_add_child(current_window, bitmap_layer_get_layer(image_layer_battery));
}

int main(void) {
	window = window_create();
	window_stack_push(window, true /* Animated */ );
	
	Layer *window_layer = window_get_root_layer(window);
	GRect bounds = layer_get_frame(window_layer);

	text_layer_percentage = text_layer_create(GRect(0,60,bounds.size.w,bounds.size.h));
	text_layer_set_font(text_layer_percentage, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
	text_layer_set_text_alignment(text_layer_percentage, GTextAlignmentCenter);
	layer_add_child(window_layer, text_layer_get_layer(text_layer_percentage));
	
	BatteryChargeState charge_state = battery_state_service_peek();
	uint8_t raw_percent = charge_state.charge_percent;
	static char percent_display_text[] = "100%";
	snprintf(percent_display_text, sizeof(percent_display_text), "%d%%", raw_percent);
	text_layer_set_text(text_layer_percentage, percent_display_text);
	
	drawBatteryBar(BATBAR_POSITION_RIGHT, BATBAR_DIRECTION_DOWN, BATBAR_COLOR_BLACK, raw_percent, window_layer);
	
	app_event_loop();
	
	text_layer_destroy(text_layer_percentage);
	window_destroy(window);
}