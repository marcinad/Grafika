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
//	{
//		if (n > tab[i])
//		{
//			n = tab[i];
//		}
//	}
//	return n;
//}
//float max(float * tab) {
//	float max = tab[0];
//	for (int i = 1; i < w; i++)
//	{
//		if (max < tab[i])
//		{
//			max = tab[i];
//		}
//	}
//	return max;
//}
//
//void RenderScene() {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glutSwapBuffers();
//}
//
//void SetupRC() {
//	glClearColor(0.6f, 0.4f, 0.12f, 1.0f);
//}
//
//void main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	glutInitWindowSize(width, heigth);
//	glutCreateWindow("Mój pierwszy program w GLUT");
//	glutDisplayFunc(RenderScene);
//	SetupRC();
//	glutMainLoop();
//	delete tmpX;
//	delete tmpY;
//}