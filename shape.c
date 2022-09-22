#include <stdio.h>
#include <math.h>
#include <time.h>
#include "shape.h"
#include "screen.h"
#include "functions.h"

// Apply the global transformation matrix
point transform_point(point in) {
	point new = {d: {0.0, 0.0}};
	for (int i = 0; i < 2; i++)
		for (int e = 0; e < 2; e++)
			new.d[i] += in.d[e] * transformation_matrix[e][i];

	return new;
}

point xy(float x, float y) {
	point out;
	out.d[0] = x;
	out.d[1] = y;
	return out;
}


// Set the transformation matrix to a given angle
void set_rotation(float angle) {
	transformation_matrix[0][0] = cos(angle);
	transformation_matrix[0][1] = -sin(angle);
	transformation_matrix[1][0] = sin(angle);
	transformation_matrix[1][1] = cos(angle);
}

int msleep(long miliseconds) {
	struct timespec rem;
	struct timespec req= {
		(int)(miliseconds / 1000),     /* secs (Must be Non-Negative) */
		(miliseconds % 1000) * 1000000 /* nano (Must be in range of 0 to 999999999) */
	};
	return nanosleep(&req , &rem);
}


//    z [2]
//   /
//  /__X [0]
// |
// |
// Y [1]

point project_point(float start[3]) {
	float rotated_point[3];
	point scaled;
	// The rotation is done in 2d, so convert to 2d
	point prerotation_xz = xy(start[0], start[2]);
	point postrotation_xz = transform_point(prerotation_xz);
	// Combine the starting point and rotated (2d) point	
	rotated_point[0] = postrotation_xz.d[0];
	rotated_point[1] = start[1];
	rotated_point[2] = postrotation_xz.d[1];
	// Traslate the cube into view.
	rotated_point[2] += 3.0;
	// Divide x and y by z to get final 2d location
	scaled.d[1] = rotated_point[1] / rotated_point[2];
	scaled.d[0] = rotated_point[0] / rotated_point[2];
	return scaled;
}

void draw_line_3d(float start[3], float end[3]) {
	point start2d;
	point end2d;
       	end2d = project_point(end);
       	start2d = project_point(start);
	draw_line(
		(int)((start2d.d[0])*40.0+40.0),
		(int)((start2d.d[1])*20.0+20.0),
		(int)((end2d.d[0])*40.0+40.0),
		(int)((end2d.d[1])*20.0+20.0)
	);
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

int main(void) {
	int frame = 0;
	while (1) {
		// Blank the screenbuffer
		clear_screen();
		// -- Drawing code start --
		// Animate rotation matrix
		float angle = (float)frame / 25;
		set_rotation(angle);
		// For all lines, draw them
		for (int i = 0; i < SHAPE_LEN; i++)
			draw_line_3d(shape[i][0], shape[i][1]);
		// -- Drawing code end --
		printscreen();
		msleep(15);
		frame++;
	}
}