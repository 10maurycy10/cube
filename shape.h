#include <stdio.h>
#include <math.h>

enum {
	P_OBLIQUE,
	P_PERSPECTIVE
};

void transform_point(float in[2], float out[2]);
void set_rotation(float angle);
void draw_line_3d(float start[3], float end[3], int mode);
