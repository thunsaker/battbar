// 2013 Thomas Hunsaker @thunsaker

#pragma once

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
	
void drawBatteryBar(const BBPosition position, const BBDirection direction, const BBColor color, uint8_t percentage, Layer *current_window);