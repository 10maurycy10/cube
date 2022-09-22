#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SCREEN_WIDTH (80)
#define SCREEN_HEIGHT (40)

// Fills screen with whitespace
void clear_screen();
// Outputs screen buffer to stdout
void printscreen();
// Draw a line in the screen buffer
void draw_line(int x1, int y1, int x2, int y2);
// Draw a string
void printstring(int x, int y, char* string);
