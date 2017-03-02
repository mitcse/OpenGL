
#include <stdlib.h>
#include <iostream>
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

#define PI 3.14159

int n; 
int cx = 0;

float si = 0.f;
int up = 1;

int ri = 0;

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

point_t points[128];
int pi;

line_t lines[128];
int li;

void plotLine (line_t l) {

	glBegin(GL_LINES);
		glVertex3f(l.p1.x/800.0, l.p1.y/800.0, 0);
		glVertex3f(l.p2.x/800.0, l.p2.y/800.0, 0);
	glEnd();	

}

void plotLines();

void display () {

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
	glLoadIdentity();                // Reset the model-view matrix

	// Scale the shit
	glScalef(si, si, si);
	si = si + 0.02 * up;
	if (si > 2) up = -1;
	if (si < 0.33) up = 1;

	// Rotate it too for the kicks
	glRotatef(ri, 0.f, 0.f, 1.f);
	ri = (ri + 1) % 360;

	plotLines();

	glFlush();

}

void addPoints () {
	// Add shape points here
	for (int i = 0; i < n; ++i) {
		float angle = i * 2 * PI / n;
		int xs = (int)(320.0 * sin(angle));
		int ys = (int)(320.0 * cos(angle));
		point_t p = getPoint(xs, ys);
		points[pi++] = p;
	}
}

void plotLines () {
	// Get and plot the lines
	li = 0;
	for (int i = 0; i < pi; ++i) {
		line_t l = getLine(points[i], points[(i + 1) % pi]);
		lines[li++] = l;
	}
	// This looks sick
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < li; ++i) {
		line_t l = lines[i];	
		// plotLine(l);
		glVertex3f(l.p1.x/800.0, l.p1.y/800.0, 0);
		// glVertex3f(l.p2.x/800.0, l.p2.y/800.0, 0);
	}	
	glEnd();
}

void update (int) { 
	// Timer for stuff
	int i = 0;
	while (i < 100) {
		i += 1;
		glutPostRedisplay();
		glutTimerFunc(50, update, 0);
	}
}

int main (int argc, char *argv []) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Pattern");

	glMatrixMode(GL_PROJECTION);      // Select the Projection matrix for operation
	glLoadIdentity();                 // Reset Projection matrix
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set clipping area's left, right, bottom, top

	glutDisplayFunc(display);

	glutTimerFunc(50, update, 0);

	li = 0;
	pi = 0;

	if (argc > 1) {
		n = atoi(argv[1]);
	} else {
		printf("Enter 'n': ");
		scanf(" %d", &n);
	}

	addPoints();

	plotLines();

	glutMainLoop();
	
	return 0;
	
}
