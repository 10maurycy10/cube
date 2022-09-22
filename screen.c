#include <stdio.h>
#include <math.h>
#include "screen.h"
#include "functions.h"

char screenbuffer[SCREEN_WIDTH][SCREEN_HEIGHT];

// Fills screen with whitespace
void clear_screen() {
	for (int x = 0; x < SCREEN_WIDTH; x++)
		for (int y = 0; y < SCREEN_HEIGHT; y++)
			screenbuffer[x][y] = ' ';
}

// Outputs screen buffer to stdout
void printscreen() {
	char line[SCREEN_WIDTH+1];
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++)
			line[x] = screenbuffer[x][y];
		line[SCREEN_WIDTH] = 0;
		printf("%s\n", line);
	}
}

// Draw a line in the screen buffer
void draw_line(int x1, int y1, int x2, int y2) {
	int dx = (x2 - x1);
	int dy = (y2 - y1);
	int steps = max(abs(dx), abs(dy));
	
	float dx_step = (float)dx / (float)steps;
	float dy_step = (float)dy / (float)steps;

	for (int step = 0; step < steps; step++) {
		float x_offset = dx_step * (float)step;
		float y_offset = dy_step * (float)step;
		int x = (int)x_offset + x1;
		int y = (int)y_offset + y1;
		screenbuffer[x][y] = '#';
	}
	
}
