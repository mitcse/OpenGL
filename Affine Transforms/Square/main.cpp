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

#define SPEED 5

using namespace std;

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

typedef struct square {
	line_t lines[4];
	point_t A, B, C, D;
} square_t;

square_t getSquare (point_t A, point_t B, point_t C, point_t D) {
	square_t sq;
	sq.lines[0] = getLine(A, B);
	sq.lines[1] = getLine(B, C);
	sq.lines[2] = getLine(C, D);
	sq.lines[3] = getLine(D, A);
	return sq;
}

square_t bigsquare;
square_t littlesquare;

void plotLine (line_t l) {
	glBegin(GL_LINES);
		glVertex3f(l.p1.x/800.0, l.p1.y/800.0, 0);
		glVertex3f(l.p2.x/800.0, l.p2.y/800.0, 0);
	glEnd();	
}

void plotSquare (square_t sq) {
	for(int i = 0; i < 4; ++i) {
		plotLine(sq.lines[i]);
	}
}

int ri = 0;

float dx = -550/800.f, dy = -550/800.f; // Current x position

int xt = 0, yt = 0;
int xinc = 0, yinc = SPEED;

void display () {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
	glLoadIdentity();                // Reset the model-view matrix

	// Push current transform matrix (identity)
	glPushMatrix();

	// Translate little square so that its centroid lies with the global origin
	glTranslatef(dx, dy, 0);

	// Rotate the little square
	glRotatef(-ri, 0.f, 0.0f, 1.0f);
	ri = (ri + SPEED) % 360;

	// Move the little square around
	glTranslatef(xt/800.f, yt/800.f, 0);

	xt += xinc;
	yt += yinc;

	// Update the delta of the origin with the centroid of the little square
	dx = (xt - 550.f)/800.f;
	dy = (yt - 550.f)/800.f;

	// Update translation deltas
	if (yt >= 1100) {
		if (xt >= 1100) {
			yinc = -SPEED;
			xinc = 0;
		} else {
			yinc = 0;
			xinc = SPEED;
		}
	} else if (yt <= 0) {
		if (xt <= 0) {
			yinc = SPEED;
			xinc = 0;
		} else {
			xinc = -SPEED;
			yinc = 0;
		}
	}

	// Translate little square back
	glTranslatef(-dx, -dy, 0);

	// Plot it
	plotSquare(littlesquare);

	// Get original matrix back
	glPopMatrix();

	// Plot big square
	plotSquare(bigsquare);

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
	glutCreateWindow("Square Rotate");

	// Call the display function
	glutDisplayFunc(display);
	glutTimerFunc(50, update, 0);

	bigsquare = getSquare(getPoint(-400, -400), getPoint(400, -400), getPoint(400, 400), getPoint(-400, 400));

	littlesquare = getSquare(getPoint(-600, -600), getPoint(-500, -600), getPoint(-500, -500), getPoint(-600, -500));

	// Main loop
	glutMainLoop();
	
	return 0;
	
}
