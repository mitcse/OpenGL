//
// main.cpp
//
// Mid point ellipse drawing algorithm.
//
// Created by @avikantz on 01/29/17
//

#include <stdlib.h>
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

typedef struct ellipse {
	int x;
	int y;
	int a;
	int b;
} ellipse_t;

ellipse_t getEllipse (int x, int y, int a, int b) {
	ellipse_t c;
	c.x = x;
	c.y = y;
	c.a = a;
	c.b = b;
	return c;
}

ellipse_t ellipses[100];
int ei;

/**
*	Plots circle points in the first octant, and their reflections in the corresponding octants.
*/
void plotEllipsePoints (int x, int y, int dx, int dy) {
	
	glBegin(GL_POINTS);

		VERTEX(x + dx, y + dy);
		VERTEX(-x + dx, y + dy);
		VERTEX(x + dx, -y + dy);
		VERTEX(-x + dx, -y + dy);

		// VERTEX( x,  y);
		// VERTEX(-x,  y);
		// VERTEX( x, -y);
		// VERTEX(-x, -y);

	glEnd();

}

// Plots a ellipse with axes c.a and c.b at center c.x, c.y
void plotEllipse (ellipse_t c) {

	// Get a random color
	color_t color = randomColor();
	glColor3f(color.r, color.g, color.b); 

	// Move to the top point of the circle.
	int x = 0;
	int y = c.b;

	int a = c.a;
	int b = c.b;

	plotEllipsePoints(x, y, c.x, c.y);

	int d = b * b - a * a * ( b - 0.25 ); // Initially, d = b^2 - a^2 b + a^2/4

	while (a * a * y >= b * b * x) { // Region R1

		if (d <= 0) {
			
			d += b * b * (3 + 2 * x); // If point is inside, d += b^2(3 + 2x); Select 'East' pixel
			x += 1;

		} else {

			d += b * b * (3 + 2 * x) + a * a * (2 - 2 * y); // If point is outside, d += b^2(3 + 2x) + a^2(2 - 2y); Select 'South East' pixel
			x += 1;
			y -= 1; 

		}

		plotEllipsePoints(x, y, c.x, c.y);

	}

	// Recalculate d (or better, not)
	// d = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;

	while (y >= 0) { // Region R2

		if (d <= 0) { // If the point is inside, d += b^2(2 + 2x) + a^2(2 - 2y); Select 'South East' pixel

			d += b * b * (2 + 2 * x) + a * a * (3 - 2 * y); 
			x += 1;
			y -= 1;

		} else { // If the point is outside, d += a^2(3 - 2y); Select 'South' pixel

			d += a * a * (3 - 2 * y);
			y -= 1;

		}

		plotEllipsePoints(x, y, c.x, c.y);

	}
 
}

void display () {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2.0);

	int i;
	for (i = 0; i < ei; ++i) {
		plotEllipse(ellipses[i]);
	}

	// Flush drawing command buffer to make drawing happen as soon as possible.
	glFlush();

}

int main (int argc, char *argv []) {
	
	// Insert code here.

	// Initialize glut, use a single buffered window in RGB mode (as opposed to a double-buffered window or color-index mode).
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Position window and give it a title.
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Ellipses");

	// Call the display function
	glutDisplayFunc(display);

	int x, y, a, b;
	ei = 0;

	// ellipse_t e = getEllipse (0, 0, 600, 400);
	// ellipses[ei++] = e;

	// Draw random ellipses
	do {
		x = rand() % 400 - 200;	
		y = rand() % 400 - 200;
		a = rand() % 800; // Axes have to be positive
		b = rand() % 600; 
		ellipse_t e = getEllipse (x, y, a, b);
		ellipses[ei++] = e;
	} while (ei < 16);

	// Main loop
	glutMainLoop();
	
	return 0;
	
}
