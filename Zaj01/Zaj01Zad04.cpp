#include "stdafx.h"
//#define _USE_MATH_DEFINES
//#include <cmath>
//#include <iostream>;
//#ifdef __APPLE__
//#include <GLUT/glut.h>
//#else
//#include <GL/glut.h>
//#endif
//
//using namespace std;
//GLfloat x = 150.0f;
//GLfloat y = 150.0f;
//
//GLsizei Size = 70;
//
//int w = 6;
//GLfloat xstep = 1.0f;
//GLfloat ystep = 1.0f;
//
//int width = 1000;
//int heigth = 600;
//
//GLfloat windowWidth;
//GLfloat windowHeight;
//GLfloat a = x;
//GLfloat b = y;
//GLfloat alfa = 0;
//float * helperX = new float[w];
//float * helperY = new float[w];
//
//float m(float * tab) {
//	float a = tab[0];
//	for (int i = 1; i < w; i++)
//		if (a > tab[i])
//			a = tab[i];
//	return a;
//}
//
//float n(float * tab) {
//	float a = tab[0];
//	for (int i = 1; i < w; i++)
//		if (a < tab[i])
//			a = tab[i];
//	return a;
//}
//
//void RenderScene() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glBegin(GL_POLYGON);
//	alfa = alfa >= 6.2 ? 0 : alfa;
//	for (int i = 0; i < w; i++)
//	{
//		float xx = x + Size * sin(2.0*M_PI*i / w);
//		float yy = y + Size * cos(2.0*M_PI*i / w);
//		float xB = a + (xx - a)*cos(alfa) - (yy - b)*sin(alfa);
//		float yB = b + (xx - a)*sin(alfa) + (yy - b)*cos(alfa);
//		helperX[i] = xB;
//		helperY[i] = yB;
//		glVertex2f(xB, yB);
//	}
//	alfa += 0.004f;
//	glEnd();
//	glutSwapBuffers();
//}
//
//void TimerFunction(int value) {
//	glutPostRedisplay();
//	glutTimerFunc(10, TimerFunction, 1);
//}
//
//void SetupRC() {
//	glClearColor(0.6f, 0.4f, 0.11f, 1.0f);
//}
//void ChangeSize(GLsizei w, GLsizei h) {
//	if (h == 0)
//		h = 1;
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	if (w <= h)
//	{
//		windowHeight = 250.0f*h / w;
//		windowWidth = 250.0f;
//	}
//	else
//	{
//		windowWidth = 250.0f*w / h;
//		windowHeight = 250.0f;
//	}
//	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//void main(int argc, char* argv[]) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(width, heigth);
//	glutCreateWindow("Mój pierwszy program w GLUT");
//	glutDisplayFunc(RenderScene);
//	glutReshapeFunc(ChangeSize);
//	glutTimerFunc(10, TimerFunction, 1);
//	SetupRC();
//	glutMainLoop();
//	delete helperX;
//	delete helperY;
//}