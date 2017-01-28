//
// main.cpp
//
// Mid point circle drawing algorithm
//
// Created by @avikantz on 01/28/17
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

circle_t circles[100];
int ci;

void plotCirclePoints (int x, int y, int dx, int dy) {
	
	glBegin(GL_POINTS);

		glVertex3f(x/800.0, y/800.0, 0);
		glVertex3f(x/800.0, -y/800.0, 0);
		glVertex3f(-x/800.0, y/800.0, 0);
		glVertex3f(-x/800.0, -y/800.0, 0);

		glVertex3f(y/800.0, x/800.0, 0);
		glVertex3f(y/800.0, -x/800.0, 0);
		glVertex3f(-y/800.0, x/800.0, 0);
		glVertex3f(-y/800.0, -x/800.0, 0);

	glEnd();

}

// Plots a circle with radius c.r at center c.x, c.y
void plotCircle (circle_t c) {

	// Get a random color
	color_t color = randomColor();
	glColor3f(color.r, color.g, color.b); 

	// Move to the top point of the circle.
	int x = 0;
	int y = c.r;

	plotCirclePoints(x, y, c.x, c.y);

	int d = 1 - c.r;

	while (y > x) {

		if (d <= 0) {
			
			d += 2 * x + 3;
			x += 1;

		} else {

			d += 2 * x - 2 * y + 5;
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
		plotCircle(circles[i]);
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
	glutCreateWindow("Circles");

	// Call the display function
	glutDisplayFunc(display);

	int x, y, r;
	ci = 0;

	// Draw random circles
	do {
		x = rand() % 800 - 400;	
		y = rand() % 800 - 400;
		r = rand() % 800 - 400;
		circle_t c = getCircle (x, y, r);
		circles[ci++] = c;
		// printf("Continue (0/1): ");
		// scanf("%d", &ch);
	} while (ci < 20);

	// Main loop
	glutMainLoop();
	
	return 0;
	
}
