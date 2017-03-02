//
// radar.cpp
//
// RADAR simulation
//
// Created by @avikantz on 02/03/17
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

#define PI 3.14159265

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

int deg = 0;

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
	// if (c.x == 0 && c.y == 0) {
	// 	color_t color = randomColor();
	// 	glColor3f(color.r, color.g, color.b); 
	// } else {
	// 	glColor3f(1, 1, 1); 
	// }

	// Gradient descent
	glColor3f(1.0 - c.r / 800.f, 1.0 - c.r / 800.f, 1.0 - c.r / 800.f); 


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

void plotLine (int x1, int y1, int x2, int y2) {
	glBegin(GL_LINES);
		VERTEX(x1, y1);
		VERTEX(x2, y2);
	glEnd();
}

void display () {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);

	// Plot the circles.
	int i;
	for (i = 0; i < ci; ++i) {
		circles[i].r = (circles[i].r + 1) % 800;
		plotCircle(circles[i]);
	}

	// Static red lines line
	glLineWidth(0.5);

	glColor3f(150/255.0, 40/255.0, 27/255.0); 

		plotLine(0, 800, 0, -800);
		plotLine(800, 0, -800, 0);

	// Rotating green line
	glLineWidth(2.0);

	glColor3f(46/255.0, 204/255.0, 113/255.0); 

	double angle = deg * PI / 180;
	plotLine(0, 0, 1200 * sin(angle), 1200 * cos(angle));
	deg = (deg + 2) % 360;

	// Flush drawing command buffer to make drawing happen as soon as possible.
	glFlush();

}

void update (int) { 
	int i = 0;
	while (i < 50) {
		i += 1;
		glutPostRedisplay();
		glutTimerFunc(50, update, 0);
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
	glutCreateWindow("Radar");

	// Call the display function
	glutDisplayFunc(display);
	glutTimerFunc(50, update, 0);

	int x, y, r;
	ci = 0;

	for (int i = 0; i < 50; ++i) {
		x = 0;
		y = 0;
		r = i * 32;
		circle_t c = getCircle (x, y, r);
		circles[ci++] = c;
	}

	// Main loop
	glutMainLoop();
	
	return 0;
	
}
