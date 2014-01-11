// 2014 Thomas Hunsaker @thunsaker
// BattBar.h
// BattBar v.1.4

#pragma once

typedef enum {
	BATTBAR_POSITION_LEFT,
	BATTBAR_POSITION_RIGHT,
	BATTBAR_POSITION_BOTTOM,
	BATTBAR_POSITION_TOP
} BBPosition;

typedef enum  {
	BATTBAR_DIRECTION_UP, // The bar will shorten toward the top of the screen
	BATTBAR_DIRECTION_DOWN // The bar will shrink toward the bottom of the screen
} BBDirection;

typedef enum {
	BATTBAR_COLOR_BLACK,
	BATTBAR_COLOR_WHITE
} BBColor;

typedef struct {
	BBPosition position;
	BBDirection direction;
	BBColor color;
	bool isWatchApp; // Determines height based on the presence of a time title bar
} BBOptions;

void SetupBattBar(BBOptions options, Layer *current_window);
void DrawBattBar();
void RefreshBattBar(BatteryChargeState charge_state);
void battbar_handler_battery(BatteryChargeState charge_state);