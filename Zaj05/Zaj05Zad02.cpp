///*
//(c) Janusz Ganczarski
//http://www.januszg.hg.pl
//JanuszG@enter.net.pl
//*/

#include "stdafx.h"

//
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//
//#include "../packages/nupengl.core.0.1.0.1/build/native/include/GL/glut.h"
//#include "../Library/colors.h"
//#include "../packages/nupengl.core.0.1.0.1/build/native/include/GL/freeglut.h"
//
//
//// sta�e do obs�ugi menu podr�cznego
//
//enum
//{
//	FULL_WINDOW,    // aspekt obrazu - ca�e okno
//	ASPECT_1_1,     // aspekt obrazu 1:1
//	EXIT            // wyj�cie
//};
//
//// aspekt obrazu
//
//int aspect = FULL_WINDOW;
//
//// rozmiary bry�y obcinania
//
//const GLdouble left = -2.0;
//const GLdouble right = 2.0;
//const GLdouble bottom = -2.0;
//const GLdouble top = 2.0;
//const GLdouble near_ = 3.0;
//const GLdouble far_ = 7.0;
//
//// k�ty obrotu
//
//GLfloat rotatex = 0.0;
//GLfloat rotatey = 0.0;
//
//// wska?nik naci�ni�cia lewego przycisku myszki
//
//int button_state = GLUT_UP;
//
//// po�o?enie kursora myszki
//
//int button_x, button_y;
//
//// sk�adowe globalnego �wiat�a otaczaj�cego
//// warto�? pocz�tkowa odpowiada warto�ci domy�lnej
//// sk�adowych tego �wiat�a
//
//GLfloat ambient_light[4] =
//{
//	0.2,0.2,0.2,1.0
//};
//
//// funkcja rysuj�ca napis w wybranym miejscu
//
//void DrawString(GLfloat x, GLfloat y, char *string)
//{
//	// po�o?enie napisu
//	glRasterPos2f(x, y);
//
//	// wy�wietlenie napisu
//	int len = strlen(string);
//	for (int i = 0; i < len; i++)
//		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
//}
//
//// funkcja generuj�ca scen� 3D
//
//void Display()
//{
//	// kolor t�a - zawarto�? bufora koloru
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//
//	// czyszczenie bufora koloru i bufora g��boko�ci
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// wyb�r macierzy modelowania
//	glMatrixMode(GL_MODELVIEW);
//
//	// macierz modelowania = macierz jednostkowa
//	glLoadIdentity();
//
//	// przesuni�cie uk�adu wsp�rz�dnych sze�cianu do �rodka bry�y odcinania
//	glTranslatef(0, 0, -(near_ + far_) / 2);
//
//	// obroty sze�cianu
//	glRotatef(rotatex, 1.0, 0, 0);
//	glRotatef(rotatey, 0, 1.0, 0);
//
//	// niewielkie powi�kszenie sze�cianu
//	glScalef(1.15, 1.15, 1.15);
//
//	// w��czenie o�wietlenia
//	glEnable(GL_LIGHTING);
//
//	// parametry globalnego �wiat�a otaczaj�cego
//	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
//
//	// w��czenie obs�ugi w�a�ciwo�ci materia��w
//	glEnable(GL_COLOR_MATERIAL);
//
//	// w�a�ciwo�ci materia�u okre�lone przez kolor wierzcho�k�w
//	glColorMaterial(GL_FRONT, GL_AMBIENT);
//
//	// w��czenie testu bufora g��boko�ci
//	glEnable(GL_DEPTH_TEST);
//
//	// rysowanie sze�cianu - 12 tr�jk�t�w
//	glBegin(GL_TRIANGLES);
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glVertex3f(1.0, -1.0, 1.0);
//	glVertex3f(1.0, 1.0, 1.0);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glVertex3f(1.0, 1.0, 1.0);
//	glVertex3f(-1.0, 1.0, 1.0);
//
//	glColor3fv(Magenta);
//	glVertex3f(-1.0, 1.0, 1.0);
//	glVertex3f(1.0, 1.0, 1.0);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glVertex3f(1.0, 1.0, 1.0);
//	glVertex3f(1.0, 1.0, -1.0);
//
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//	glVertex3f(1.0, 1.0, 1.0);
//	glVertex3f(1.0, -1.0, 1.0);
//	glVertex3f(1.0, 1.0, -1.0);
//	glVertex3f(1.0, -1.0, 1.0);
//	glVertex3f(1.0, -1.0, -1.0);
//
//	glColor3fv(Lime);
//	glVertex3f(1.0, -1.0, -1.0);
//	glVertex3f(1.0, -1.0, 1.0);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glVertex3f(1.0, -1.0, 1.0);
//	glVertex3f(-1.0, -1.0, 1.0);
//
//	glColor3fv(Blue);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glVertex3f(-1.0, 1.0, 1.0);
//
//	glColor3fv(Yellow);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glVertex3f(1.0, 1.0, -1.0);
//	glVertex3f(1.0, -1.0, -1.0);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glVertex3f(1.0, 1.0, -1.0);
//
//	// koniec definicji sze�cianu
//	glEnd();
//
//	// wy��czenie o�wietlenia
//	glDisable(GL_LIGHTING);
//
//	// wy��czenie obs�ugi w�a�ciwo�ci materia��w
//	glDisable(GL_COLOR_MATERIAL);
//
//	// wy�wietlenie sk�adowych globalnego �wiat�a otaczaj�cego
//	char string[100];
//	GLfloat rgba[4];
//	glColor3fv(Black);
//
//	// pobranie warto�ci sk�adowych �wiat�a otaczaj�cego
//	// (oczywi�cie warto�ci te odpowiadaj� tablicy ambient_light)
//	glGetFloatv(GL_LIGHT_MODEL_AMBIENT, rgba);
//	sprintf_s(string, "AMBIENT: R=%f G=%f B=%f A=%f", rgba[0], rgba[1], rgba[2], rgba[3]);
//
//	// trzeba odpowiednio przekszta�ci? uk�ad wsp�rz�dnych
//	// aby napis znajdowa� si� na samej "g�rze" bry�y obcinania
//	glLoadIdentity();
//	glTranslatef(0, 0, -near_);
//
//	// narysowanie napisu
//	DrawString(left, bottom, string);
//
//	// skierowanie polece? do wykonania
//	glFlush();
//
//	// zamiana bufor�w koloru
//	glutSwapBuffers();
//}
//
//// zmiana wielko�ci okna
//
//void Reshape(int width, int height)
//{
//	// obszar renderingu - ca�e okno
//	glViewport(0, 0, width, height);
//
//	// wyb�r macierzy rzutowania
//	glMatrixMode(GL_PROJECTION);
//
//	// macierz rzutowania = macierz jednostkowa
//	glLoadIdentity();
//
//	// parametry bry�y obcinania
//	if (aspect == ASPECT_1_1)
//	{
//		// wysoko�? okna wi�ksza od wysoko�ci okna
//		if (width < height && width > 0)
//			glFrustum(left, right, bottom*height / width, top*height / width, near_, far_);
//		else
//
//			// szeroko�? okna wi�ksza lub r�wna wysoko�ci okna
//			if (width >= height && height > 0)
//				glFrustum(left*width / height, right*width / height, bottom, top, near_, far_);
//	}
//	else
//		glFrustum(left, right, bottom, top, near_, far_);
//
//	// generowanie sceny 3D
//	Display();
//}
//
//// obs�uga klawiatury
//
//void Keyboard(unsigned char key, int x, int y)
//{
//	// zmiana warto�ci sk�adowej R
//	if (key == 'R' && ambient_light[0] < 1.0)
//		ambient_light[0] += 0.05;
//	else
//		if (key == 'r' && ambient_light[0] > -1.0)
//			ambient_light[0] -= 0.05;
//
//	// zmiana warto�ci sk�adowej G
//	if (key == 'G' && ambient_light[1] < 1.0)
//		ambient_light[1] += 0.05;
//	else
//		if (key == 'g' && ambient_light[1] > -1.0)
//			ambient_light[1] -= 0.05;
//
//	// zmiana warto�ci sk�adowej B
//	if (key == 'B' && ambient_light[2] < 1.0)
//		ambient_light[2] += 0.05;
//	else
//		if (key == 'b' && ambient_light[2] > -1.0)
//			ambient_light[2] -= 0.05;
//
//	// narysowanie sceny
//	Display();
//}
//
//// obs�uga klawiszy funkcyjnych i klawiszy kursora
//
//void SpecialKeys(int key, int x, int y)
//{
//	switch (key)
//	{
//		// kursor w lewo
//	case GLUT_KEY_LEFT:
//		rotatey -= 1;
//		break;
//
//		// kursor w g�r�
//	case GLUT_KEY_UP:
//		rotatex -= 1;
//		break;
//
//		// kursor w prawo
//	case GLUT_KEY_RIGHT:
//		rotatey += 1;
//		break;
//
//		// kursor w d�
//	case GLUT_KEY_DOWN:
//		rotatex += 1;
//		break;
//	}
//
//	// odrysowanie okna
//	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//}
//
//// obs�uga przycisk�w myszki
//
//void MouseButton(int button, int state, int x, int y)
//{
//	if (button == GLUT_LEFT_BUTTON)
//	{
//		// zapami�tanie stanu lewego przycisku myszki
//		button_state = state;
//
//		// zapami�tanie po�o?enia kursora myszki
//		if (state == GLUT_DOWN)
//		{
//			button_x = x;
//			button_y = y;
//		}
//	}
//}
//
//// obs�uga ruchu kursora myszki
//
//void MouseMotion(int x, int y)
//{
//	if (button_state == GLUT_DOWN)
//	{
//		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
//		button_x = x;
//		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
//		button_y = y;
//		glutPostRedisplay();
//	}
//}
//
//// obs�uga menu podr�cznego
//
//void Menu(int value)
//{
//	switch (value)
//	{
//		// obszar renderingu - ca�e okno
//	case FULL_WINDOW:
//		aspect = FULL_WINDOW;
//		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//		break;
//
//		// obszar renderingu - aspekt 1:1
//	case ASPECT_1_1:
//		aspect = ASPECT_1_1;
//		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//		break;
//
//		// wyj�cie
//	case EXIT:
//		exit(0);
//	}
//}
//
//int main(int argc, char *argv[])
//{
//	// inicjalizacja biblioteki GLUT
//	glutInit(&argc, argv);
//
//	// inicjalizacja bufora ramki
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//
//	// rozmiary g��wnego okna programu
//	glutInitWindowSize(500, 500);
//
//	// utworzenie g��wnego okna programu
//#ifdef WIN32
//
//	glutCreateWindow("Globalne �wiat�o otaczaj�ce");
//#else
//
//	glutCreateWindow("Globalne swiatlo otaczajace");
//#endif
//
//	// do��czenie funkcji generuj�cej scen� 3D
//	glutDisplayFunc(Display);
//
//	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
//	glutReshapeFunc(Reshape);
//
//	// do��czenie funkcji obs�ugi klawiatury
//	glutKeyboardFunc(Keyboard);
//
//	// do��czenie funkcji obs�ugi klawiszy funkcyjnych i klawiszy kursora
//	glutSpecialFunc(SpecialKeys);
//
//	// obs�uga przycisk�w myszki
//	glutMouseFunc(MouseButton);
//
//	// obs�uga ruchu kursora myszki
//	glutMotionFunc(MouseMotion);
//
//	// utworzenie menu podr�cznego
//	glutCreateMenu(Menu);
//
//	// utworzenie podmenu - aspekt obrazu
//	int MenuAspect = glutCreateMenu(Menu);
//#ifdef WIN32
//
//	glutAddMenuEntry("Aspekt obrazu - ca�e okno", FULL_WINDOW);
//#else
//
//	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
//#endif
//
//	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);
//
//	// menu g��wne
//	glutCreateMenu(Menu);
//	glutAddSubMenu("Aspekt obrazu", MenuAspect);
//#ifdef WIN32
//
//	glutAddMenuEntry("Wyj�cie", EXIT);
//#else
//
//	glutAddMenuEntry("Wyjscie", EXIT);
//#endif
//
//	// okre�lenie przycisku myszki obs�uguj�cej menu podr�czne
//	glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//	// wprowadzenie programu do obs�ugi p�tli komunikat�w
//	glutMainLoop();
//	return 0;
//}
