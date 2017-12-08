#include "Button.h"
#include <sstream>
#include <cstring>
using namespace std;
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

Button::Button() {
	x = 0; y = 0; width = 0; height = 0;
}

Button::Button(double xcoord, double ycoord, double w, double h) {
	x = xcoord;
	y = ycoord;
	width = w;
	height = h;
}

void Button::drawButton() {
	glBegin(GL_POLYGON);
		glVertex2f(x, y);  // upper left
		glVertex2f(x, y + height);  // lower left
		glVertex2f(x + width, y + height);  // lower right
		glVertex2f(x + width, y);  // upper right
	glEnd();
}

void Button::drawButton(double *pos) {
	x = pos[0];
	y = pos[1];
	width = pos[2];
	height = pos[3];
	drawButton();
}

void Button::drawText(const char* text) {
	glColor3f(1.0f, 1.0f, 0.0f);
	glRasterPos2f( x, y );
	int length = strlen(text);
	for (int i = 0; i < length; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

void Button::drawText(double x, double y, const char* text) {
	glColor3f(1.0f, 1.0f, 0.0f);
	glRasterPos2f( x, y );
	int length = strlen(text);
	for (int i = 0; i < length; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

void Button::drawNumber(double x, double y, double num) {
	stringstream oss;
	oss << num; oss.flush();
	drawText(x, y, oss.str().c_str());
}