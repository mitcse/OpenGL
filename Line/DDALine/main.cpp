#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

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
	r = rand() % 255 + 1;
	color.g = r / 255.f;
	r = rand() % 255 + 1;
	color.b = r / 255.f;
	return color;
}

void display () {

	// Set every pixel in the frame buffer to the current clear color.
	glClear(GL_COLOR_BUFFER_BIT);

	color_t color = randomColor();
	glColor3f(color.r, color.g, color.b); 
	glLineWidth(4.0);
	
	glBegin(GL_LINES);

	glVertex3f(0.8, 0.8, 0);
	glVertex3f(-0.8, -0.8, 0);

	glEnd();

	color = randomColor();
	glColor3f(color.r, color.g, color.b); 

	glBegin(GL_LINES);

	glVertex3f(0.8, -0.8, 0);
	glVertex3f(-0.8, 0.8, 0);

	glEnd();

	color = randomColor();
	glColor3f(color.r, color.g, color.b); 

	glBegin(GL_LINES);

	glVertex3f(0, -0.8, 0);
	glVertex3f(0.8, 0, 0);
	glVertex3f(0, 0.8, 0);
	glVertex3f(-0.8, 0, 0);

	glEnd();

	color = randomColor();
	glColor3f(color.r, color.g, color.b); 

	glBegin(GL_LINES);

	glVertex3f(0.8, 0, 0);
	glVertex3f(0, 0.8, 0);
	glVertex3f(-0.8, 0, 0);
	glVertex3f(0, -0.8, 0);

	glEnd();

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

	// Main loop
	glutMainLoop();
	
	return 0;
	
}
