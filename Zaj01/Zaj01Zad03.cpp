#include "stdafx.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>;
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;
GLfloat x = 150.0f;
GLfloat y = 150.0f;

GLsizei Size = 60;

int w = 6;
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

int width = 1000;
int heigth = 600;

GLfloat windowWidth;
GLfloat windowHeight;
float * tmpX = new float[w];
float * tmpY = new float[w];
float n(float * tab) {
	float n = tab[0];
	for (int i = 1; i < w; i++)
		if (n > tab[i])
			n = tab[i];

	return n;
}
float m(float * tab) {
	float m = tab[0];
	for (int i = 1; i < w; i++)
		if (m < tab[i])
			m = tab[i];

	return m;
}

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	for (int i = 0; i < w; i++)
	{
		float xx = x + Size * sin(2.0*M_PI*i / w);
		float yy = y + Size * cos(2.0*M_PI*i / w);
		tmpX[i] = xx;
		tmpY[i] = yy;

		glVertex2f(xx, yy);
	}
	glEnd();
	glutSwapBuffers();
}

void TimerFunction(int value) {

	float minFromX = n(tmpX);
	float maxFromX = m(tmpX);
	float minFromY = n(tmpY);
	float maxFromY = m(tmpY);

	if (x > windowWidth - Size || x < Size)
		xstep = -xstep;
	if (y > windowHeight - Size || y < Size - minFromY)
		ystep = -ystep;

	x += xstep;
	y += ystep;
	glutReshapeWindow(width, heigth);
	glutPostRedisplay();
	glutTimerFunc(10, TimerFunction, 1);
}

void SetupRC() {

	glClearColor(0.6f, 0.4f, 0.12f, 1.0f);
}
void ChangeSize(GLsizei w, GLsizei h) {
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void main(int argc, char* argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, heigth);
	glutCreateWindow("Mój pierwszy program w GLUT");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(10, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
	delete tmpX;
	delete tmpY;
}
