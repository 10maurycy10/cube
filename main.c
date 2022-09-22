#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "shape.h"
#include "screen.h"
#include "functions.h"

int msleep(long miliseconds) {
	struct timespec rem;
	struct timespec req= {
		(int)(miliseconds / 1000),     /* secs (Must be Non-Negative) */
		(miliseconds % 1000) * 1000000 /* nano (Must be in range of 0 to 999999999) */
	};
	return nanosleep(&req , &rem);
}

#define SHAPE_LEN 12
// All the lines in a cube!
float shape[SHAPE_LEN][2][3] = {
        {{1.0, 1.0, 1.0},{1.0, 1.0, -1.0}},
        {{1.0, -1.0, 1.0},{1.0, -1.0, -1.0}},
        {{-1.0, 1.0, 1.0},{-1.0, 1.0, -1.0}},
        {{-1.0, -1.0, 1.0},{-1.0, -1.0, -1.0}},
        {{1.0, 1.0, 1.0},{1.0, -1.0, 1.0}},
        {{1.0, -1.0, 1.0},{-1.0, -1.0, 1.0}},
        {{-1.0, 1.0, 1.0},{1.0, 1.0, 1.0}},
        {{-1.0, -1.0, 1.0},{-1.0, 1.0, 1.0}},
        {{1.0, 1.0, -1.0},{1.0, -1.0, -1.0}},
        {{1.0, -1.0, -1.0},{-1.0, -1.0, -1.0}},
        {{-1.0, 1.0, -1.0},{1.0, 1.0, -1.0}},
        {{-1.0, -1.0, -1.0},{-1.0, 1.0, -1.0}},
};

int main(int argc, char **argv) {
	int mode = P_PERSPECTIVE;
	if (argc > 1) {
		char* modes = argv[1];
		if (0==strncmp(modes,"oblique", 3)) {
			mode = P_OBLIQUE;
		} else if (0==strncmp(modes,"perspective", 3)) {
			mode = P_PERSPECTIVE;
		} else {
			printf("Usage: %s [MODE]\n", argv[0]);
			printf("MODE is 'perspective' or 'oblique'.\n");
			return 1;
		}
	}
	char statusline[512];
	int frame = 0;
	// Set stdout to fully buffered
	setvbuf(stdout, NULL, _IOFBF, 4096);
	while (1) {
		// Blank the screenbuffer
		clear_screen();
		// -- Drawing code start --
		// Animate rotation matrix
		float angle = (float)frame / 50;
		set_rotation(angle);
		// For all lines, draw them
		for (int i = 0; i < SHAPE_LEN; i++)
			draw_line_3d(shape[i][0], shape[i][1], mode);
		// Draw text
		snprintf(statusline, 512, "Cube. %d Lines; Frame %d",SHAPE_LEN, frame);
		printstring(0,SCREEN_HEIGHT - 1,statusline);
		// -- Drawing code end --
		printscreen();
		fflush(stdout);
		msleep(15);
		frame++;
	}
}

