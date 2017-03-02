
#include <stdlib.h>
#include <iostream>

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

int n; 

typedef struct line {
	int x1, y1;
	int x2, y2;
} line_t;

line_t getLine (int x1, int y1, int x2, int y2) {
	line_t l;
	l.x1 = x1;
	l.y1 = y1;
	l.x2 = x2;
	l.y2 = y2;
	return l;
}

line_t lines[128];
int li;

void plotLine (line_t l) {

	glBegin(GL_LINES);
		glVertex3f(l.x1/800.0, l.y1/800.0, 0);
		glVertex3f(l.x2/800.0, l.y2/800.0, 0);
	glEnd();	

}

void display () {

	glClear(GL_COLOR_BUFFER_BIT);

	int i;
	for (i = 0; i < li; ++i) {
		line_t line = lines[i];
		plotLine(line);
	}

	glFlush();

}

void addLines (float xs[4], float ys[4], int count) {
	if (count == n) {
		return;
	}

	for (int i = 0; i < 4; ++i) {
		line_t line = getLine((int)xs[i], (int)ys[i], (int)xs[(i+1)%4], (int)ys[(i+1)%4]);
		lines[li++] = line;
	}

	float nxs[4], nys[4];
	for (int i = 0; i < 4; ++i) {
		nxs[i] = (xs[i] + xs[(i+1)%4]) / 2.f;
		nys[i] = (ys[i] + ys[(i+1)%4]) / 2.f;
	}

	addLines(nxs, nys, count + 1);
}

int main (int argc, char *argv []) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Pattern");

	glutDisplayFunc(display);

	li = 0;
	
	printf("Enter 'n': ");
	scanf(" %d", &n);

	float xs[4] = {-640, -640, 640, 640};

	float ys[4] = {-640, 640, 640, -640};

	addLines(xs, ys, 0);

	// int i;
	// for (i = 0; i < li; ++i) {
	// 	if (i % 4 == 0)
	// 		printf("\n");
	// 	line_t line = lines[i];
	// 	printf("{(%4d, %4d), (%4d, %4d)}\n", line.x1, line.y1, line.x2, line.y2);
	// }

	glutMainLoop();
	
	return 0;
	
}
