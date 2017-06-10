#include "stdafx.h"
//
///*
//(c) Janusz Ganczarski
//http://www.januszg.hg.pl
//JanuszG@enter.net.pl
//*/
//
//#include <GL/glut.h>
//#include <stdlib.h>
//#include "../Library/master.h"
//
//// sta³e do obs³ugi menu podrêcznego
//
//enum
//{
//	FULL_WINDOW = GL_ALWAYS + 100, // aspekt obrazu - ca³e okno
//	ASPECT_1_1, // aspekt obrazu 1:1
//	EXIT // wyjœcie
//};
//
//// aspekt obrazu
//
//int aspect = FULL_WINDOW;
//
//// rozmiary bry³y obcinania
//
//const GLdouble left = -2.0;
//const GLdouble right = 2.0;
//const GLdouble bottom = -2.0;
//const GLdouble top = 2.0;
//const GLdouble near_ = 3.0;
//const GLdouble far_ = 7.0;
//
//// k¹ty obrotu
//
//GLfloat rotatex = 0.0;
//GLfloat rotatey = 0.0;
//
//// wskaŸnik naciœniêcia lewego przycisku myszki
//
//int button_state = GLUT_UP;
//
//// po³o¿enie kursora myszki
//
//int button_x, button_y;
//
//// rodzaj testu bufora g³êbokoœci
//
//GLenum depth_test = GL_LESS;
//
//// funkcja generuj¹ca scenê 3D
//
//void Display()
//{
//	// kolor t³a - zawartoœæ bufora koloru
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//
//	// czyszczenie bufora koloru i bufora g³êbokoœci
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// wybór macierzy modelowania
//	glMatrixMode(GL_MODELVIEW);
//
//	// macierz modelowania = macierz jednostkowa
//	glLoadIdentity();
//
//	// przesuniêcie uk³adu wspó³rzêdnych szeœcianu do œrodka bry³y odcinania
//	glTranslatef(0, 0, -(near_ + far_) / 2);
//
//	// obroty szeœcianu
//	glRotatef(rotatex, 1.0, 0, 0);
//	glRotatef(rotatey, 0, 1.0, 0);
//
//	// niewielkie powiêkszenie szeœcianu
//	glScalef(1.15, 1.15, 1.15);
//
//	// w³¹czenie testu bufora g³êbokoœci
//	glEnable(GL_DEPTH_TEST);
//
//	// wybór funkcji do testu bufora g³êbokoœci
//	glDepthFunc(depth_test);
//
//	// rysowanie szeœcianu RGB - 12 trójk¹tów
//	glBegin(GL_TRIANGLES);
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glColor3fv(Yellow);
//	glVertex3f(1.0, -1.0, 1.0);
//	glColor3fv(White);
//	glVertex3f(1.0, 1.0, 1.0);
//
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glColor3fv(White);
//	glVertex3f(1.0, 1.0, 1.0);
//	glColor3fv(Magenta);
//	glVertex3f(-1.0, 1.0, 1.0);
//
//	glColor3fv(Magenta);
//	glVertex3f(-1.0, 1.0, 1.0);
//	glColor3fv(White);
//	glVertex3f(1.0, 1.0, 1.0);
//	glColor3fv(Blue);
//	glVertex3f(-1.0, 1.0, -1.0);
//
//	glColor3fv(Blue);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glColor3fv(White);
//	glVertex3f(1.0, 1.0, 1.0);
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//	glColor3fv(White);
//	glVertex3f(1.0, 1.0, 1.0);
//	glColor3fv(Yellow);
//	glVertex3f(1.0, -1.0, 1.0);
//
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//	glColor3fv(Yellow);
//	glVertex3f(1.0, -1.0, 1.0);
//	glColor3fv(Lime);
//	glVertex3f(1.0, -1.0, -1.0);
//
//	glColor3fv(Lime);
//	glVertex3f(1.0, -1.0, -1.0);
//	glColor3fv(Yellow);
//	glVertex3f(1.0, -1.0, 1.0);
//	glColor3fv(Black);
//	glVertex3f(-1.0, -1.0, -1.0);
//
//	glColor3fv(Black);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glColor3fv(Yellow);
//	glVertex3f(1.0, -1.0, 1.0);
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//
//	glColor3fv(Black);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glColor3fv(Blue);
//	glVertex3f(-1.0, 1.0, -1.0);
//
//	glColor3fv(Blue);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glColor3fv(Red);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glColor3fv(Magenta);
//	glVertex3f(-1.0, 1.0, 1.0);
//
//	glColor3fv(Black);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glColor3fv(Blue);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//
//	glColor3fv(Lime);
//	glVertex3f(1.0, -1.0, -1.0);
//	glColor3fv(Black);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glColor3fv(Cyan);
//	glVertex3f(1.0, 1.0, -1.0);
//
//	// koniec definicji szeœcianu RGB
//	glEnd();
//
//	// skierowanie poleceñ do wykonania
//	glFlush();
//
//	// zamiana buforów koloru
//	glutSwapBuffers();
//}
//
//// zmiana wielkoœci okna
//
//void Reshape(int width, int height)
//{
//	// obszar renderingu - ca³e okno
//	glViewport(0, 0, width, height);
//
//	// wybór macierzy rzutowania
//	glMatrixMode(GL_PROJECTION);
//
//	// macierz rzutowania = macierz jednostkowa
//	glLoadIdentity();
//
//	// parametry bry³y obcinania
//	if (aspect == ASPECT_1_1)
//	{
//		// wysokoœæ okna wiêksza od wysokoœci okna
//		if (width < height && width > 0)
//			glFrustum(left, right, bottom * height / width, top * height / width, near_, far_);
//		else
//
//			// szerokoœæ okna wiêksza lub równa wysokoœci okna
//			if (width >= height && height > 0)
//				glFrustum(left * width / height, right * width / height, bottom, top, near_, far_);
//
//	}
//	else
//		glFrustum(left, right, bottom, top, near_, far_);
//
//	// generowanie sceny 3D
//	Display();
//}
//
//// obs³uga klawiszy funkcyjnych i klawiszy kursora
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
//		// kursor w górê
//	case GLUT_KEY_UP:
//		rotatex -= 1;
//		break;
//
//		// kursor w prawo
//	case GLUT_KEY_RIGHT:
//		rotatey += 1;
//		break;
//
//		// kursor w dó³
//	case GLUT_KEY_DOWN:
//		rotatex += 1;
//		break;
//	}
//
//	// odrysowanie okna
//	Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//}
//
//// obs³uga przycisków myszki
//
//void MouseButton(int button, int state, int x, int y)
//{
//	if (button == GLUT_LEFT_BUTTON)
//	{
//		// zapamiêtanie stanu lewego przycisku myszki
//		button_state = state;
//
//		// zapamiêtanie po³o¿enia kursora myszki
//		if (state == GLUT_DOWN)
//		{
//			button_x = x;
//			button_y = y;
//		}
//	}
//}
//
//// obs³uga ruchu kursora myszki
//
//void MouseMotion(int x, int y)
//{
//	if (button_state == GLUT_DOWN)
//	{
//		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) *(x - button_x);
//		button_x = x;
//		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) *(button_y - y);
//		button_y = y;
//		glutPostRedisplay();
//	}
//}
//
//// obs³uga menu podrêcznego
//
//void Menu(int value)
//{
//	switch (value)
//	{
//		// obszar renderingu - ca³e okno
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
//		// test bufora g³êbokoœci: GL_NEVER
//	case GL_NEVER:
//		depth_test = GL_NEVER;
//		Display();
//		break;
//
//		// test bufora g³êbokoœci: GL_LESS
//	case GL_LESS:
//		depth_test = GL_LESS;
//		Display();
//		break;
//
//		// test bufora g³êbokoœci: GL_EQUAL
//	case GL_EQUAL:
//		depth_test = GL_EQUAL;
//		Display();
//		break;
//
//		// test bufora g³êbokoœci: GL_LEQUAL
//	case GL_LEQUAL:
//		depth_test = GL_LEQUAL;
//		Display();
//		break;
//
//		// test bufora g³êbokoœci: GL_GREATER
//	case GL_GREATER:
//		depth_test = GL_GREATER;
//		Display();
//		break;
//
//		// test bufora g³êbokoœci: GL_NOTEQUAL
//	case GL_NOTEQUAL:
//		depth_test = GL_NOTEQUAL;
//		Display();
//		break;
//
//		// test bufora g³êbokoœci: GL_GEQUAL
//	case GL_GEQUAL:
//		depth_test = GL_GEQUAL;
//		Display();
//		break;
//
//		// test bufora g³êbokoœci: GL_ALWAYS
//	case GL_ALWAYS:
//		depth_test = GL_ALWAYS;
//		Display();
//		break;
//
//		// wyjœcie
//	case EXIT:
//		exit(0);
//	}
//}
//
//int main(int argc, char * argv[])
//{
//	// inicjalizacja biblioteki GLUT
//	glutInit(&argc, argv);
//
//	// inicjalizacja bufora ramki
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//
//	// rozmiary g³ównego okna programu
//	glutInitWindowSize(500, 500);
//
//	// utworzenie g³ównego okna programu
//#ifdef WIN32
//
//	glutCreateWindow("Szeœcian 5");
//#else
//
//	glutCreateWindow("Szescian 5");
//#endif
//
//	// do³¹czenie funkcji generuj¹cej scenê 3D
//	glutDisplayFunc(Display);
//
//	// do³¹czenie funkcji wywo³ywanej przy zmianie rozmiaru okna
//	glutReshapeFunc(Reshape);
//
//	// do³¹czenie funkcji obs³ugi klawiszy funkcyjnych i klawiszy kursora
//	glutSpecialFunc(SpecialKeys);
//
//	// obs³uga przycisków myszki
//	glutMouseFunc(MouseButton);
//
//	// obs³uga ruchu kursora myszki
//	glutMotionFunc(MouseMotion);
//
//	// utworzenie menu podrêcznego
//	glutCreateMenu(Menu);
//
//	// utworzenie podmenu - aspekt obrazu
//	int MenuAspect = glutCreateMenu(Menu);
//#ifdef WIN32
//
//	glutAddMenuEntry("Aspekt obrazu - ca³e okno", FULL_WINDOW);
//#else
//
//	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
//#endif
//
//	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);
//
//	// utworzenie podmenu - Test z-bufora
//	int MenuZbuffer = glutCreateMenu(Menu);
//	glutAddMenuEntry("GL_NEVER", GL_NEVER);
//	glutAddMenuEntry("GL_LESS", GL_LESS);
//	glutAddMenuEntry("GL_EQUAL", GL_EQUAL);
//	glutAddMenuEntry("GL_LEQUAL", GL_LEQUAL);
//	glutAddMenuEntry("GL_GREATER", GL_GREATER);
//	glutAddMenuEntry("GL_NOTEQUAL", GL_NOTEQUAL);
//	glutAddMenuEntry("GL_GEQUAL", GL_GEQUAL);
//	glutAddMenuEntry("GL_ALWAYS", GL_ALWAYS);
//
//	// menu g³ówne
//	glutCreateMenu(Menu);
//	glutAddSubMenu("Aspekt obrazu", MenuAspect);
//	glutAddSubMenu("Test z-bufora", MenuZbuffer);
//#ifdef WIN32
//
//	glutAddMenuEntry("Wyjœcie", EXIT);
//#else
//
//	glutAddMenuEntry("Wyjscie", EXIT);
//#endif
//
//	// okreœlenie przycisku myszki obs³uguj¹cej menu podrêczne
//	glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//	// wprowadzenie programu do obs³ugi pêtli komunikatów
//	glutMainLoop();
//	return 0;
//}
