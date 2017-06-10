#include "stdafx.h"
//
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
//GLsizei Size = 60;
//
//int width = 1000;
//int heigth = 600;
//
//int w = 6;
//
//GLfloat xstep = 1.0f;
//GLfloat ystep = 1.0f;
//
//
//GLfloat windowWidth;
//GLfloat windowHeight;
//float * tmpX = new float[w];
//float * tmpY = new float[w];
//float min(float * tab) {
//	float n = tab[0];
//	for (int i = 1; i < w; i++)
//		if (n > tab[i])
//			n = tab[i];
//
//	return n;
//}
//float max(float * tab) {
//	float max = tab[0];
//	for (int i = 1; i < w; i++)
//		if (max < tab[i])
//			max = tab[i];
//
//	return max;
//}
//
//void RenderScene() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glBegin(GL_POLYGON);
//	for (int i = 0; i < w; i++)
//	{
//		float xx = x + Size * sin(2.0*M_PI*i / w);
//		float yy = y + Size * cos(2.0*M_PI*i / w);
//		tmpX[i] = xx;
//		tmpY[i] = yy;
//
//		glVertex2f(xx, yy);
//	}
//	glEnd();
//	glutSwapBuffers();
//}
//
//void SetupRC() {
//
//	glClearColor(0.6f, 0.4f, 0.12f, 1.0f);
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
//
//void main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(width, heigth);
//	glutCreateWindow("Mój pierwszy program w GLUT");
//	glutDisplayFunc(RenderScene);
//	glutReshapeFunc(ChangeSize);
//	SetupRC();
//	glutMainLoop();
//	delete tmpX;
//	delete tmpY;
//}