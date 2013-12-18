// 2013 Thomas Hunsaker @thunsaker
// Main.c
// BattBar v.1.1

#include <pebble.h>
#include "battbar.h"

static Window *window;

static TextLayer *text_layer_percentage;

int main(void) {
	window = window_create();
	window_stack_push(window, true);
	
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
	
	/* Change these options to your liking */
	BBOptions options;
	options.position = BATTBAR_POSITION_TOP;
	options.direction = BATTBAR_DIRECTION_DOWN;
	options.color = BATTBAR_COLOR_BLACK;
	options.isWatchApp = true;
	DrawBattBar(options, window_layer);
	
	app_event_loop();
	
	text_layer_destroy(text_layer_percentage);
	window_destroy(window);
}