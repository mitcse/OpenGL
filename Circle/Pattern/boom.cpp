//
// boom.cpp
//
// Circular animation.
//
// Created by @avikantz on 01/28/17
//

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <math.h>

#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#endif

#define VERTEX(X, Y) glVertex3f((X)/800.0, (Y)/800.0, 0);

using namespace std;

typedef struct color {
	float r, g, b;
} color_t;

color_t randomColor () {
	color_t color;
	int r;
	r = rand() % 255 + 1;
	color.r = r / 255.f;
	r = (r + rand()) % 255 + 1;
	color.g = r / 255.f;
	r = (r + rand()) % 255 + 1;
	color.b = r / 255.f;
	return color;
}

typedef struct circle {
	int x;
	int y;
	int r;
} circle_t;

circle_t getCircle (int x, int y, int r) {
	circle_t c;
	c.x = x;
	c.y = y;
	c.r = r;
	return c;
}

circle_t circles[256];
int ci;

/**
*	Plots circle points in the first octant, and their reflections in the corresponding octants.
*/
void plotCirclePoints (int x, int y, int dx, int dy) {
	
	glBegin(GL_POINTS);

		VERTEX(x + dx, y + dy);
		VERTEX(-x + dx, y + dy);
		VERTEX(x + dx, -y + dy);
		VERTEX(-x + dx, -y + dy);

		VERTEX(y + dx, x + dy);
		VERTEX(-y + dx, x + dy);
		VERTEX(y + dx, -x + dy);
		VERTEX(-y + dx, -x + dy);

	glEnd();

}

// Plots a circle with radius c.r at center c.x, c.y
void plotCircle (circle_t c) {

	// Get a random color
	if (c.x == 0 && c.y == 0) {
		color_t color = randomColor();
		glColor3f(color.r, color.g, color.b); 
	} else {
		glColor3f(1, 1, 1); 
	}

	// Move to the top point of the circle.
	int x = 0;
	int y = c.r;

	plotCirclePoints(x, y, c.x, c.y);

	int d = 1 - c.r; // Initially, d = 1 - R

	while (y > x) {

		if (d <= 0) {
			
			d += 2 * x + 3; // If point is inside, d += 2x + 3
			x += 1;

		} else {

			d += 2 * x - 2 * y + 5; // If point is outside, d += 2x - 2y + 5
			x += 1;
			y -= 1; 

		}

		plotCirclePoints(x, y, c.x, c.y);

	}

}

void display () {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2.0);

	int i;
	for (i = 0; i < ci; ++i) {
		circles[i].r = (circles[i].r + 1) % 400;
		plotCircle(circles[i]);
	}

	// Flush drawing command buffer to make drawing happen as soon as possible.
	glFlush();

}

void update (int) { 
	int i = 0;
	while (i < 100) {
		i += 1;
		glutPostRedisplay();
		glutTimerFunc(100, update, 0);
	}
}

int main (int argc, char *argv []) {
	
	// Insert code here.

	// Initialize glut, use a single buffered window in RGB mode (as opposed to a double-buffered window or color-index mode).
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Position window and give it a title.
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Circles");

	// Call the display function
	glutDisplayFunc(display);

	glutTimerFunc(100, update, 0);

	int x, y, r;
	ci = 0;

	for (int i = 0; i < 40; ++i) {
		x = 0;
		y = 0;
		r = i * 16;
		circle_t c = getCircle (x, y, r);
		circles[ci++] = c;
	}

	for (int j = 0; j < 4; ++j) {
		x = 320 * ((j < 2) ? 1 : -1);
		y = 320 * ((j % 2 == 0) ? 1 : -1);
		for (int i = 0; i < 25; ++i) {
			r = i * 16;
			circle_t c = getCircle (x, y, r);
			circles[ci++] = c;
		}
	}

	x = 453;
	y = 453;
	for (int j = 0; j < 4; ++j) {
		x = 453 * ((j % 2 == 0) ? 1 : -1);
		y = 453 * ((j % 2 == 0) ? 1 : -1); 
		for (int i = 0; i < 25; ++i) {
			r = i * 16;
			circle_t c = getCircle ((j < 2) * x, (j > 1) * y, r);
			circles[ci++] = c;
		}
	}

	/*
	// Draw random circles
	do {
		x = rand() % 400 - 200;	
		y = rand() % 400 - 200;
		r = abs(rand() % 1200 - 600); // Radius has to be positive
		circle_t c = getCircle (x, y, r);
		circles[ci++] = c;
	} while (ci < 16);
	*/

	// Main loop
	glutMainLoop();
	
	return 0;
	
}
