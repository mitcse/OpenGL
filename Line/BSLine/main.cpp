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

typedef struct line {
	int x1, y1;
	int x2, y2;
} line_t;

line_t getLine (int x1, int y1, int x2, int y2) {
	line_t l;
	l.x1 = min(x1, x2);
	l.y1 = y1;
	l.x2 = max(x1, x2);
	l.y2 = y2;
	return l;
}

line_t lines[128];
int li;

void plotPoint (int x, int y) {
	
	glBegin(GL_POINTS);

		glVertex3f(x/800.0, y/800.0, 0);

	glEnd();

}

// Plots a line between two points using Bresenham's line drawing algorithm
void plotLine (line_t l) {

	// Get a random color
	color_t color = randomColor();
	glColor3f(color.r, color.g, color.b); 

	int dx = l.x2 - l.x1;
	int dy = l.y2 - l.y1;

	int d;

	if (l.y2 > l.y1) {
		if (dy > dx) {
			d = 2 * dy - dx;
		} else {
			d = 2 * dx - dy;
		}
	} else {
		if (dy > dx) {
			d = - 2 * dy - dx;
		} else {
			d = 2 * dx - dy;
		}
	}

	int x = l.x1;
	int y = l.y1;

	for (; x <= l.x2; ++x) {
		plotPoint(x, y);
		if (l.y2 > l.y1) {
			if (dy > dx) {
				if (d > 0) {
					y += 1;
					d -= dx;
				}
				d += 2 * dy;
			} else {
				if (d > 0) {
					x += 1;
					d -= dx;
				}
				d += 2 * dy;
			}
		} else {
			if (dy > dx) {
				d = - 2 * dy - dx;
			} else {
				d = 2 * dx - dy;
			}
		}

	}

}

void display () {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);

	int i;
	for (i = 0; i < li; ++i) {
		line_t line = lines[i];
		plotLine(line);
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
	glutCreateWindow("Open GL Demo");

	// Call the display function
	glutDisplayFunc(display);

	int x1, y1, x2, y2;
	int ch;
	li = 0;
	// do {
	// 	printf("Enter coordinates: (x1, y1, x2, y2): ");
	// 	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	// 	line_t line = getLine(x1, y1, x2, y2);
	// 	lines[li++] = line;
	// 	printf("Continue (0/1): ");
	// 	scanf("%d", &ch);
	// } while (ch == 1 && li < 128);

	// Draw random lines...
	do {
		x1 = rand() % 1600 - 800;
		x2 = rand() % 1600 - 800;
		y1 = rand() % 1600 - 800;
		y2 = rand() % 1600 - 800;
		line_t line = getLine(x1, y1, x2, y2);
		lines[li++] = line;
		// printf("Continue (0/1): ");
		// scanf("%d", &ch);
	} while (li < 40);

	// Main loop
	glutMainLoop();
	
	return 0;
	
}
