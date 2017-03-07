//
// main.cpp
//
// Wheel rotate?
//
// Created by @avikantz on 03/07/17
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

circle_t circle;

typedef struct point  {
	int x;
	int y;
} point_t;

point_t getPoint (int x, int y) {
	point_t p;
	p.x = x;
	p.y = y;
	return p;
}

typedef struct line {
	point_t p1;
	point_t p2;
} line_t;

line_t getLine (point_t p1, point_t p2) {
	line_t l;
	l.p1 = p1;
	l.p2 = p2;
	return l;
}

line_t lines[4];
line_t axes;

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
	// color_t color = randomColor();
	// glColor3f(color.r, color.g, color.b); 

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

void plotLine (line_t l) {

	glBegin(GL_LINES);
		glVertex3f(l.p1.x/800.0, l.p1.y/800.0, 0);
		glVertex3f(l.p2.x/800.0, l.p2.y/800.0, 0);
	glEnd();	

}

int ri = 0;
int ti = 0;
int inc = 2;

float cx = 0; // Current x position

void display () {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
	glLoadIdentity();                // Reset the model-view matrix

	glPushMatrix();

	glLineWidth(1.0);

	glTranslatef(cx, 0.25f, 0.0);
	// glPushMatrix();

	glRotatef(-ri * inc / 2, 0.f, 0.0f, 1.0f);
	ri = (ri + 1) % 360;
	// glPopMatrix();

	glTranslatef(ti/800.f, 0, 0);
	cx = ti/800.f;

	glTranslatef(-cx, -0.25f, 0.0);

	ti += inc;
	if (ti >= 600) {
		inc = -2;
	} 
	if (ti <= -600) {
		inc = 2;
	}

	plotCircle(circle);
	for (int i = 0; i < 4; ++i) {
		plotLine(lines[i]);
	}

	glPopMatrix();

	// Plot axes.
	glLineWidth(2.0);
	plotLine(axes);

	// Flush drawing command buffer to make drawing happen as soon as possible.
	glFlush();

}


void update (int) { 
	int i = 0;
	while (i < 50) {
		i += 1;
		glutPostRedisplay();
		glutTimerFunc(20, update, 0);
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
	glutCreateWindow("Wheel");

	// Call the display function
	glutDisplayFunc(display);
	glutTimerFunc(50, update, 0);

	circle = getCircle(0, 200, 200);

	axes = getLine(getPoint(-800, 0), getPoint(800, 0));

	lines[0] = getLine(getPoint(0, 0), getPoint(0, 400));
	lines[1] = getLine(getPoint(-200, 200), getPoint(200, 200));
	// lines[2] = getLine(getPoint(-117, 117), getPoint(117, 117));
	// lines[3] = getLine(getPoint(0, 0), getPoint(0, 400));

	// Main loop
	glutMainLoop();
	
	return 0;
	
}
