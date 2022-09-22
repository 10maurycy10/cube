#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 40

float transformation_matrix[2][2];

typedef struct point {
	float d[2];
} point;

point transform_point(point in);
void set_rotation(float angle);
