
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

int di = 0;

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

line_t lines[128 * 127];
int li;

void plotLine (line_t l) {

	glBegin(GL_LINES);
		glVertex3f(l.p1.x/800.0, l.p1.y/800.0, 0);
		glVertex3f(l.p2.x/800.0, l.p2.y/800.0, 0);
	glEnd();	

}

void display () {

	glClear(GL_COLOR_BUFFER_BIT);

	cx = (cx + 1) % 360;

	int i;
	for (i = 0; i < di; ++i) {
		// float q = fabs(sin(PI * cx * (i + 1) / 180)); 
		// glColor3f(q, q, q);
		line_t line = lines[i];	
		plotLine(line);
	}
	di = (di + 1 < li) ? di + 1: li;

	glFlush();

}

void addPoints () {
	for (int i = 0; i < n; ++i) {
		float angle = i * 2 * PI / n;
		int xs = (int)(640.0 * sin(angle));
		int ys = (int)(640.0 * cos(angle));
		point_t p = getPoint(xs, ys);
		points[pi++] = p;
	}
}

void addLines () {
	for (int i = 0; i < pi; ++i) {
		for (int j = i + 1; j < pi; ++j) {
			line_t l = getLine(points[i], points[j]);
			lines[li++] = l;
		}
	}
}

void update (int) { 
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
	addLines();

	glutMainLoop();
	
	return 0;
	
}
