#include <stdio.h>
#include <math.h>
#include <time.h>
#include "shape.h"
#include "screen.h"
#include "functions.h"

float transformation_matrix[2][2];

// Apply the global transformation matrix
void transform_point(float in[2], float out[2]) {
	out[0] = 0.0;
	out[1] = 0.0;
	for (int i = 0; i < 2; i++)
		for (int e = 0; e < 2; e++)
			out[i] += in[e] * transformation_matrix[e][i];
}

// Set the transformation matrix to a given angle
void set_rotation(float angle) {
	transformation_matrix[0][0] = cos(angle);
	transformation_matrix[0][1] = -sin(angle);
	transformation_matrix[1][0] = sin(angle);
	transformation_matrix[1][1] = cos(angle);
}

//    z [2]
//   /
//  /__X [0]
// |
// |
// Y [1]

// Aply the world roatation to a 3d point
void rotate_point_3d(float start[3], float end[3]) {
	float prerotation_xz[2] = {start[0], start[2]};
	float postrotation_xz[2];
	transform_point(prerotation_xz, postrotation_xz);
	// Combine the starting point and rotated (2d) point	
	end[0] = postrotation_xz[0];
	end[1] = start[1];
	end[2] = postrotation_xz[1];
}

// Projects a point from World space to screen space, taking perspecitve into account
void project_point_perspective(float start[3], float out[2]) {
	float rotated_point[3];
	rotate_point_3d(start, rotated_point);
	// Traslate the cube into view.
	rotated_point[2] += 3.5;
	// Divide x and y by z to get final 2d location
	out[1] = rotated_point[1] / rotated_point[2];
	out[0] = rotated_point[0] / rotated_point[2];
}

// Projects a point from World space to screen space, using isometric perspective
void project_point_oblique(float start[3], float out[2]) {
	float rotated_point[3];
	rotate_point_3d(start, rotated_point);
	out[0] = rotated_point[0] + (rotated_point[2] / 2);
	out[1] = rotated_point[1] - (rotated_point[2] / 2);
	out[0] /= 4;
	out[1] /= 4;
}

void draw_line_3d(float start[3], float end[3], int perspective) {
	float start2d[2];
	float end2d[2];
	switch (perspective) {
		case P_OBLIQUE:
       			project_point_oblique(end, end2d);
		       	project_point_oblique(start, start2d);
			break;
		case P_PERSPECTIVE:
       			project_point_perspective(end, end2d);
		       	project_point_perspective(start, start2d);
			break;
	}
	draw_line(
		(int)((start2d[0])*SCREEN_WIDTH+(SCREEN_WIDTH/2)),
		(int)((start2d[1])*SCREEN_HEIGHT+(SCREEN_HEIGHT/2)),
		(int)((end2d[0])*SCREEN_WIDTH+(SCREEN_WIDTH/2)),
		(int)((end2d[1])*SCREEN_HEIGHT+(SCREEN_HEIGHT/2))
	);
}
