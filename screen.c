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
	printf("\e[1;1H\e[2J"); // Clear the screen
	char line[SCREEN_WIDTH+1];
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++)
			line[x] = screenbuffer[x][y];
		line[SCREEN_WIDTH] = 0;
		printf("%s\n", line);
	}
}

void printstring(int x, int y,char* string) {
	// For all chars in the string
	for (char* c = string; *c; c++) {
		if (x < SCREEN_WIDTH && x >= 0)
			if (y < SCREEN_HEIGHT && y >= 0)
				screenbuffer[x++][y] = *c;
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
		if (x < SCREEN_WIDTH && x >= 0)
			if (y < SCREEN_HEIGHT && y >= 0)
				screenbuffer[x][y] = '#';
	}
	
}
