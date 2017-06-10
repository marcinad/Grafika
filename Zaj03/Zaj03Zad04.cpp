#include "stdafx.h"
//
//#include <GL/glut.h>
//#include "../Library/glext.h"
//#ifndef WIN32
//#define GLX_GLXEXT_LEGACY
//#include <GL/glx.h>
//#define wglGetProcAddress glXGetProcAddressARB
//#endif
//#include <stdlib.h>
//#include <stdio.h>
//#include "../Library/colors.h"
//#include "../Zaj03/targa.h"
//// wska?nik na funkcj� glWindowPos2i
//PFNGLWINDOWPOS2IPROC glWindowPos2i = NULL;
//// sta�e do obs�ugi menu podr�cznego
//enum
//{
//	PERSPECTIVE_CORRECTION_FASTEST, // korekcja perspektywy - GL_FASTEST
//	PERSPECTIVE_CORRECTION_DONT_CARE, // korekcja perspektywy - GL_DONT_CARE
//	PERSPECTIVE_CORRECTION_NICEST, // korekcja perspektywy - GL_NICEST
//	GENERATE_MIPMAP_FASTEST, // jako�� generowania mipmap - GL_FASTEST
//	GENERATE_MIPMAP_DONT_CARE, // jako�� generowania mipmap - GL_DONT_CARE
//	GENERATE_MIPMAP_NICEST, // jako�� generowania mipmap - GL_NICEST
//	FULL_WINDOW, // aspekt obrazu - ca�e okno
//	ASPECT_1_1, // aspekt obrazu 1:1
//	EXIT // wyj�cie
//};
//// aspekt obrazu
//int aspect = FULL_WINDOW;
//// usuni�cie definicji makr near i far
//#ifdef near
//#undef near
//#endif
//#ifdef far
//#undef far
//#endif
//// rozmiary bry�y obcinania
//const GLdouble left = -2.0;
//const GLdouble right = 2.0;
//const GLdouble bottom = -2.0;
//const GLdouble top = 2.0;
//const GLdouble near = 3.0;
//const GLdouble far = 7.0;
//// k�ty obrotu
//GLfloat rotatex = 0.0;
//GLfloat rotatey = 0.0;
//// wska?nik naci�ni�cia lewego przycisku myszki
//int button_state = GLUT_UP;
//// po�o?enie kursora myszki
//int button_x, button_y;
//// wsp�czynnik skalowania
//GLfloat scale = 1.5;
//// identyfikatory tekstur
//GLuint GROUND, WOOD, ROOF, WINDOW;
//// identyfikatory list wy�wietlania
//GLint GROUND_LIST, WOOD_LIST, ROOF_LIST, WINDOW_LIST;
//// filtr pomniejszaj�cy
//GLint min_filter = GL_LINEAR_MIPMAP_LINEAR;
//// wskaz�wki do korekcji perspektywy przy renderingu tekstur
//GLint perspective_correction_hint = GL_DONT_CARE;
//// wskaz�wki do automatycznego generowania mipmap
//GLint mipmap_generation_hint = GL_DONT_CARE;
//// funkcja rysuj�ca napis w wybranym miejscu
//// (wersja korzystaj�ca z funkcji glWindowPos2i)
//void DrawString(GLint x, GLint y, char *string)
//{
//	// po�o?enie napisu
//	glWindowPos2i(x, y);
//	// wy�wietlenie napisu
//	int len = strlen(string);
//	for (int i = 0; i < len; i++)
//		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
//}
//// funkcja generuj�ca scen� 3D
//void DisplayScene()
//{
//	// kolor t�a - zawarto�� bufora koloru
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	// czyszczenie bufora koloru i bufora g��boko�ci
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	// wyb�r macierzy modelowania
//	glMatrixMode(GL_MODELVIEW);
//	// macierz modelowania = macierz jednostkowa
//	glLoadIdentity();
//	// przesuni�cie uk�adu wsp�rz�dnych obiekt�w do �rodka bry�y odcinania
//	glTranslatef(0.0, 0.0, -(near + far) / 2);
//	// obroty obiektu
//	glRotatef(rotatex, 1.0, 0.0, 0.0);
//	glRotatef(rotatey, 0.0, 1.0, 0.0);
//	// skalowanie obiektu - klawisze "+" i "-"
//	glScalef(scale, scale, scale);
//	// w��czenie testu bufora g��boko�ci
//	glEnable(GL_DEPTH_TEST);
//	// w��czenie teksturowania dwuwymiarowego
//	glEnable(GL_TEXTURE_2D);
//	// filtr powi�kszaj�cy
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	// filtr pomniejszaj�cy
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
//	// wskaz�wki do korekcji perspektywy przy renderingu tekstur
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, perspective_correction_hint);
//	// ustawienie paramet�w �rodowiska tekstur
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//	// rysowanie pod�o?a
//	glBindTexture(GL_TEXTURE_2D, GROUND);
//	glPushMatrix();
//	glTranslatef(0.0, -1.0, 0.0);
//	glCallList(GROUND_LIST);
//	glPopMatrix();
//	// rysowanie �cian domku
//	glBindTexture(GL_TEXTURE_2D, WOOD);
//	glPushMatrix();
//	glTranslatef(0.0, -0.5, 0.0);
//	glScalef(0.5, 0.5, 0.5);
//	glCallList(WOOD_LIST);
//	glPopMatrix();
//	//WINDOW
//	glBindTexture(GL_TEXTURE_2D, WINDOW);
//	glPushMatrix();
//	glTranslatef(0.0, -0.5, 0.0);
//	glScalef(0.5, 0.5, 0.5);
//	glCallList(WINDOW_LIST);
//	glPopMatrix();
//	//WINDOW
//	// rysowanie dachu domku
//	glBindTexture(GL_TEXTURE_2D, ROOF);
//	glPushMatrix();
//	glTranslatef(0.0, -0.5, 0.0);
//	glScalef(0.5, 0.5, 0.5);
//	glCallList(ROOF_LIST);
//	glPopMatrix();
//	// wy��czenie teksturowania dwuwymiarowego
//	glDisable(GL_TEXTURE_2D);
//	// wy�wietlenie wybranych informacje
//	char string[200];
//	GLint var;
//	glColor3fv(Black);
//	// pobranie informacji o filtrze pomniejszaj�cy
//	glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &var);
//	switch (var)
//	{
//		// filtr GL_NEAREST_MIPMAP_NEAREST
//	case GL_NEAREST_MIPMAP_NEAREST:
//		sprintf(string, "GL_TEXTURE_MIN_FILTER = GL_NEAREST_MIPMAP_NEAREST");
//		break;
//		// filtr GL_NEAREST_MIPMAP_LINEAR
//	case GL_NEAREST_MIPMAP_LINEAR:
//		sprintf(string, "GL_TEXTURE_MIN_FILTER = GL_NEAREST_MIPMAP_LINEAR");
//		break;
//		// filtr GL_LINEAR_MIPMAP_NEAREST
//	case GL_LINEAR_MIPMAP_NEAREST:
//		sprintf(string, "GL_TEXTURE_MIN_FILTER = GL_LINEAR_MIPMAP_NEAREST");
//		break;
//		// filtr GL_LINEAR_MIPMAP_LINEAR
//	case GL_LINEAR_MIPMAP_LINEAR:
//		sprintf(string, "GL_TEXTURE_MIN_FILTER = GL_LINEAR_MIPMAP_LINEAR");
//		break;
//	}
//	DrawString(2, glutGet(GLUT_WINDOW_HEIGHT) - 17, string);
//	// pobranie informacji o wskaz�wkach do automatycznego generowania mipmap
//	glGetIntegerv(GL_PERSPECTIVE_CORRECTION_HINT, &var);
//	switch (var)
//	{
//	case GL_FASTEST:
//		sprintf(string, "GL_PERSPECTIVE_CORRECTION_HINT = GL_FASTEST");
//		break;
//	case GL_DONT_CARE:
//		sprintf(string, "GL_PERSPECTIVE_CORRECTION_HINT = GL_DONT_CARE");
//		break;
//	case GL_NICEST:
//		sprintf(string, "GL_PERSPECTIVE_CORRECTION_HINT = GL_NICEST");
//		break;
//	}
//	DrawString(2, glutGet(GLUT_WINDOW_HEIGHT) - 33, string);
//	// pobranie informacji o wskaz�wkach do korekcji perspektywy przy renderingu tekstur
//	glGetIntegerv(GL_GENERATE_MIPMAP_HINT, &var);
//	switch (var)
//	{
//	case GL_FASTEST:
//		sprintf(string, "GL_GENERATE_MIPMAP_HINT = GL_FASTEST");
//		break;
//	case GL_DONT_CARE:
//		sprintf(string, "GL_GENERATE_MIPMAP_HINT = GL_DONT_CARE");
//		break;
//	case GL_NICEST:
//		sprintf(string, "GL_GENERATE_MIPMAP_HINT = GL_NICEST");
//		break;
//	}
//	DrawString(2, glutGet(GLUT_WINDOW_HEIGHT) - 49, string);
//	// skierowanie polece? do wykonania
//	glFlush();
//	// zamiana bufor�w koloru
//	glutSwapBuffers();
//}
//// zmiana wielko�ci okna
//void Reshape(int width, int height)
//{
//	// obszar renderingu - ca�e okno
//	glViewport(0, 0, width, height);
//	// wyb�r macierzy rzutowania
//	glMatrixMode(GL_PROJECTION);
//	// macierz rzutowania = macierz jednostkowa
//	glLoadIdentity();
//	// parametry bry�y obcinania
//	if (aspect == ASPECT_1_1)
//	{
//		// wysoko�� okna wi�ksza od wysoko�ci okna
//		if (width < height && width > 0)
//			glFrustum(left, right, bottom*height / width, top*height / width, near, far);
//		else
//			// szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
//			if (width >= height && height > 0)
//				glFrustum(left*width / height, right*width / height, bottom, top, near,
//					far);
//	}
//	else
//		glFrustum(left, right, bottom, top, near, far);
//	// generowanie sceny 3D
//	DisplayScene();
//}
//// obs�uga klawiatury
//void Keyboard(unsigned char key, int x, int y)
//{
//	// klawisz +
//	if (key == '+')
//		scale += 0.05;
//	else
//		// klawisz -
//		if (key == '-' && scale > 0.05)
//			scale -= 0.05;
//	// narysowanie sceny
//	DisplayScene();
//}
//// obs�uga przycisk�w myszki
//void MouseButton(int button, int state, int x, int y)
//{
//	if (button == GLUT_LEFT_BUTTON)
//	{
//		// zapami�tanie stanu lewego przycisku myszki
//		button_state = state;
//		// zapami�tanie po�o?enia kursora myszki
//		if (state == GLUT_DOWN)
//		{
//			button_x = x;
//			button_y = y;
//		}
//	}
//}
//// obs�uga ruchu kursora myszki
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
//// utworzenie tekstur
//void GenerateTextures()
//{
//	// zmienne u?yte przy obs�udze plik�w TARGA
//	GLsizei width, height;
//	GLenum format, type;
//	GLvoid *pixels;
//	// tryb upakowania bajt�w danych tekstury
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	// wskaz�wki do automatycznego generowania mipmap
//	glHint(GL_GENERATE_MIPMAP_HINT, mipmap_generation_hint);
//	// wczytanie tekstury ground1-2.tga
//	GLboolean error = load_targa("ground1-2.tga", width, height, format, type, pixels);
//	if (error == GL_FALSE)
//	{
//		printf("Niepoprawny odczyt pliku ground1-2.tga");
//		exit(0);
//	}
//	glGenTextures(1, &GROUND);
//	glBindTexture(GL_TEXTURE_2D, GROUND);
//	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, type, pixels);
//	delete[](unsigned char*)pixels;
//	error = load_targa("wall.tga", width, height, format, type, pixels);
//	if (error == GL_FALSE)
//	{
//		printf("Niepoprawny odczyt pliku wall_wood_verti_color.tga");
//		exit(0);
//	}
//	glGenTextures(1, &WOOD);
//	glBindTexture(GL_TEXTURE_2D, WOOD);
//	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, type, pixels);
//	delete[](unsigned char*)pixels;
//	error = load_targa("roof_old_rectangle_color.tga", width, height, format, type, pixels);
//	if (error == GL_FALSE)
//	{
//		printf("Niepoprawny odczyt pliku roof_old_rectangle_color.tga");
//		exit(0);
//	}
//	glGenTextures(1, &ROOF);
//	glBindTexture(GL_TEXTURE_2D, ROOF);
//	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, type, pixels);
//	delete[](unsigned char*)pixels;
//	error = load_targa("windows.tga", width, height, format, type, pixels);
//	if (error == GL_FALSE)
//	{
//		printf("Niepoprawny odczyt pliku windows.tga.tga");
//		exit(0);
//	}
//	glGenTextures(1, &WINDOW);
//	glBindTexture(GL_TEXTURE_2D, WINDOW);
//	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, type, pixels);
//	delete[](unsigned char*)pixels;
//}
//// obs�uga menu podr�cznego
//void Menu(int value)
//{
//	switch (value)
//	{
//		// filtr pomniejszaj�cy
//	case GL_NEAREST_MIPMAP_NEAREST:
//	case GL_NEAREST_MIPMAP_LINEAR:
//	case GL_LINEAR_MIPMAP_NEAREST:
//	case GL_LINEAR_MIPMAP_LINEAR:
//		min_filter = value;
//		DisplayScene();
//		break;
//		// wskaz�wka GL_FASTEST do korekcji perspektywy przy renderingu tekstur
//	case PERSPECTIVE_CORRECTION_FASTEST:
//		perspective_correction_hint = GL_FASTEST;
//		DisplayScene();
//		break;
//		// wskaz�wka GL_DONT_CARE do korekcji perspektywy przy renderingu tekstur
//	case PERSPECTIVE_CORRECTION_DONT_CARE:
//		perspective_correction_hint = GL_DONT_CARE;
//		DisplayScene();
//		break;
//		// wskaz�wka GL_NICEST do korekcji perspektywy przy renderingu tekstur
//	case PERSPECTIVE_CORRECTION_NICEST:
//		perspective_correction_hint = GL_NICEST;
//		DisplayScene();
//		break;
//		// wskaz�wka do automatycznego generowania mipmap
//	case GENERATE_MIPMAP_FASTEST:
//		GenerateTextures();
//		mipmap_generation_hint = GL_FASTEST;
//		DisplayScene();
//		break;
//		// wskaz�wka GL_DONT_CARE do automatycznego generowania mipmap
//	case GENERATE_MIPMAP_DONT_CARE:
//		GenerateTextures();
//		mipmap_generation_hint = GL_DONT_CARE;
//		DisplayScene();
//		break;
//		// wskaz�wka GL_NICEST do automatycznego generowania mipmap
//	case GENERATE_MIPMAP_NICEST:
//		GenerateTextures();
//		mipmap_generation_hint = GL_NICEST;
//		DisplayScene();
//		break;
//		// obszar renderingu - ca�e okno
//	case FULL_WINDOW:
//		aspect = FULL_WINDOW;
//		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//		break;
//		// obszar renderingu - aspekt 1:1
//	case ASPECT_1_1:
//		aspect = ASPECT_1_1;
//		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//		break;
//		// wyj�cie
//	case EXIT:
//		exit(0);
//	}
//}
//// utworzenie list wy�wietlania
//void GenerateDisplayLists()
//{
//	// generowanie identyfikatora pierwszej listy wy�wietlania
//	GROUND_LIST = glGenLists(1);
//	// pierwsza lista wy�wietlania - pod�o?e
//	glNewList(GROUND_LIST, GL_COMPILE);
//	// czworok�t
//	glBegin(GL_QUADS);
//	glTexCoord2f(16.0, 0.0);
//	glVertex3f(-8.0, 0.0, -8.0);
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(-8.0, 0.0, 8.0);
//	glTexCoord2f(0.0, 16.0);
//	glVertex3f(8.0, 0.0, 8.0);
//	glTexCoord2f(16.0, 16.0);
//	glVertex3f(8.0, 0.0, -8.0);
//	glEnd();
//	// koniec pierwszej listy wy�wietlania
//	glEndList();
//	//
//	WINDOW_LIST = glGenLists(1);
//	// druga lista wy�wietlania - �ciany chatki
//	glNewList(WINDOW_LIST, GL_COMPILE);
//	// seria tr�jk�t�w
//	glBegin(GL_TRIANGLES);
//	// prawa boczna �ciana
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(1.0, 1.0, -1.0);
//	glTexCoord2f(2.0, 0.0);
//	glVertex3f(1.0, 1.0, 1.0);
//	glTexCoord2f(2.0, 2.0);
//	glVertex3f(1.0, -1.0, 1.0);
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(1.0, 1.0, -1.0);
//	glTexCoord2f(2.0, 2.0);
//	glVertex3f(1.0, -1.0, 1.0);
//	glTexCoord2f(0.0, 2.0);
//	glVertex3f(1.0, -1.0, -1.0);
//	// lewa boczna �ciana
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glTexCoord2f(2.0, 0.0);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glTexCoord2f(0.0, 2.0);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glTexCoord2f(0.0, 2.0);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glTexCoord2f(2.0, 0.0);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glTexCoord2f(2.0, 2.0);
//	glVertex3f(-1.0, 1.0, 1.0);
//	glEnd();
//	glEndList();
//	// generowanie identyfikatora drugiej listy wy�wietlania
//	WOOD_LIST = glGenLists(1);
//	// druga lista wy�wietlania - �ciany chatki
//	glNewList(WOOD_LIST, GL_COMPILE);
//	// seria tr�jk�t�w
//	glBegin(GL_TRIANGLES);
//	// przednia �ciana
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glTexCoord2f(2.0, 0.0);
//	glVertex3f(1.0, -1.0, 1.0);
//	glTexCoord2f(2.0, 2.0);
//	glVertex3f(1.0, 1.0, 1.0);
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(-1.0, -1.0, 1.0);
//	glTexCoord2f(2.0, 2.0);
//	glVertex3f(1.0, 1.0, 1.0);
//	glTexCoord2f(0.0, 2.0);
//	glVertex3f(-1.0, 1.0, 1.0);
//	//// prawa boczna �ciana
//	//glTexCoord2f(0.0, 0.0);
//	//glVertex3f(1.0, 1.0, -1.0);
//	//glTexCoord2f(2.0, 0.0);
//	//glVertex3f(1.0, 1.0, 1.0);
//	//glTexCoord2f(2.0, 2.0);
//	//glVertex3f(1.0, -1.0, 1.0);
//	//glTexCoord2f(0.0, 0.0);
//	//glVertex3f(1.0, 1.0, -1.0);
//	//glTexCoord2f(2.0, 2.0);
//	//glVertex3f(1.0, -1.0, 1.0);
//	//glTexCoord2f(0.0, 2.0);
//	//glVertex3f(1.0, -1.0, -1.0);
//	//// lewa boczna �ciana
//	//glTexCoord2f(0.0, 0.0);
//	//glVertex3f(-1.0, -1.0, -1.0);
//	//glTexCoord2f(2.0, 0.0);
//	//glVertex3f(-1.0, -1.0, 1.0);
//	//glTexCoord2f(0.0, 2.0);
//	//glVertex3f(-1.0, 1.0, -1.0);
//	//glTexCoord2f(0.0, 2.0);
//	//glVertex3f(-1.0, 1.0, -1.0);
//	//glTexCoord2f(2.0, 0.0);
//	//glVertex3f(-1.0, -1.0, 1.0);
//	//glTexCoord2f(2.0, 2.0);
//	//glVertex3f(-1.0, 1.0, 1.0);
//	// tylna �ciana
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glTexCoord2f(0.0, 2.0);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glTexCoord2f(2.0, 0.0);
//	glVertex3f(1.0, 1.0, -1.0);
//	glTexCoord2f(2.0, 2.0);
//	glVertex3f(1.0, -1.0, -1.0);
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(-1.0, -1.0, -1.0);
//	glTexCoord2f(2.0, 0.0);
//	glVertex3f(1.0, 1.0, -1.0);
//	// przedni szczyt
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(-1.0, 1.0, 1.0);
//	glTexCoord2f(0.0, 2.0);
//	glVertex3f(1.0, 1.0, 1.0);
//	glTexCoord2f(1.0, 2.0);
//	glVertex3f(0.0, 2.0, 1.0);
//	// tylny szczyt
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(-1.0, 1.0, -1.0);
//	glTexCoord2f(1.0, 2.0);
//	glVertex3f(0.0, 2.0, -1.0);
//	glTexCoord2f(0.0, 2.0);
//	glVertex3f(1.0, 1.0, -1.0);
//	glEnd();
//	// koniec drugiej listy wy�wietlania
//	glEndList();
//	// generowanie identyfikatora trzeciej listy wy�wietlania
//	ROOF_LIST = glGenLists(1);
//	// trzecia lista wy�wietlania - dach chatki
//	glNewList(ROOF_LIST, GL_COMPILE);
//	// dwa czworok�ty
//	glBegin(GL_QUADS);
//	// lewa cz�� dachu
//	glTexCoord2f(2.0, 2.0);
//	glVertex3f(0.0, 2.0, 1.2);
//	glTexCoord2f(0.0, 2.0);
//	glVertex3f(0.0, 2.0, -1.2);
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(-1.0, 1.0, -1.2);
//	glTexCoord2f(2.0, 0.0);
//	glVertex3f(-1.0, 1.0, 1.2);
//	// prawa cz�� dachu
//	glTexCoord2f(2.0, 2.0);
//	glVertex3f(0.0, 2.0, -1.2);
//	glTexCoord2f(0.0, 2.0);
//	glVertex3f(0.0, 2.0, 1.2);
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(1.0, 1.0, 1.2);
//	glTexCoord2f(2.0, 0.0);
//	glVertex3f(1.0, 1.0, -1.2);
//	glEnd();
//	// koniec trzeciej listy wy�wietlania
//	glEndList();
//}
//// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze?
//void ExtensionSetup()
//{
//	// pobranie numeru wersji biblioteki OpenGL
//	const char *version = (char*)glGetString(GL_VERSION);
//	// odczyt wersji OpenGL
//	int major = 0, minor = 0;
//	if (sscanf(version, "%d.%d", &major, &minor) != 2)
//	{
//#ifdef WIN32
//		printf("B��dny format wersji OpenGL\n");
//#else
//		printf("Bledny format wersji OpenGL\n");
//#endif
//		exit(0);
//	}
//	// sprawdzenie czy jest co najmniej wersja 1.4 OpenGL lub
//	// czy jest obs�ugiwane rozszerzenie GL_SGIS_generate_mipmap
//	if (!(major > 1 || minor >= 4) &&
//		!glutExtensionSupported("GL_SGIS_generate_mipmap"))
//	{
//		printf("Brak rozszerzenia GL_SGIS_generate_mipmap!\n");
//		exit(0);
//	}
//	// sprawdzenie czy jest co najmniej wersja 1.4
//	if (major > 1 || minor >= 4)
//	{
//		// pobranie wska?nika wybranej funkcji OpenGL 1.4
//		glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress("glWindowPos2i");
//	}
//	else
//		// sprawdzenie czy jest obs�ugiwane rozszerzenie ARB_window_pos
//		if (glutExtensionSupported("GL_ARB_window_pos"))
//		{
//			// pobranie wska?nika wybranej funkcji rozszerzenia ARB_window_pos
//			glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress
//			("glWindowPos2iARB");
//		}
//		else
//		{
//			printf("Brak rozszerzenia ARB_window_pos!\n");
//			exit(0);
//		}
//}
//int main(int argc, char *argv[])
//{
//	// inicjalizacja biblioteki GLUT
//	glutInit(&argc, argv);
//	// inicjalizacja bufora ramki
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	// rozmiary g��wnego okna programu
//	glutInitWindowSize(500, 500);
//	// utworzenie g��wnego okna programu
//	glutCreateWindow("Mipmapy 2D");
//	// do��czenie funkcji generuj�cej scen� 3D
//	glutDisplayFunc(DisplayScene);
//	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
//	glutReshapeFunc(Reshape);
//	// do��czenie funkcji obs�ugi klawiatury
//	glutKeyboardFunc(Keyboard);
//	// obs�uga przycisk�w myszki
//	glutMouseFunc(MouseButton);
//	// obs�uga ruchu kursora myszki
//	glutMotionFunc(MouseMotion);
//	// utworzenie podmenu - Filtr pomniejszaj�cy
//	int MenuMinFilter = glutCreateMenu(Menu);
//	glutAddMenuEntry("GL_NEAREST_MIPMAP_NEAREST", GL_NEAREST_MIPMAP_NEAREST);
//	glutAddMenuEntry("GL_NEAREST_MIPMAP_LINEAR", GL_NEAREST_MIPMAP_LINEAR);
//	glutAddMenuEntry("GL_LINEAR_MIPMAP_NEAREST", GL_LINEAR_MIPMAP_NEAREST);
//	glutAddMenuEntry("GL_LINEAR_MIPMAP_LINEAR", GL_LINEAR_MIPMAP_LINEAR);
//	// utworzenie podmenu - GL_PERSPECTIVE_CORRECTION_HINT
//	int PerspectiveCorrectionHint = glutCreateMenu(Menu);
//	glutAddMenuEntry("GL_FASTEST", PERSPECTIVE_CORRECTION_FASTEST);
//	glutAddMenuEntry("GL_DONT_CARE", PERSPECTIVE_CORRECTION_DONT_CARE);
//	glutAddMenuEntry("GL_NICEST", PERSPECTIVE_CORRECTION_NICEST);
//	// utworzenie podmenu - GL_GENERATE_MIPMAP_HINT
//	int GenerateMipmapHint = glutCreateMenu(Menu);
//	glutAddMenuEntry("GL_FASTEST", GENERATE_MIPMAP_FASTEST);
//	glutAddMenuEntry("GL_DONT_CARE", GENERATE_MIPMAP_DONT_CARE);
//	glutAddMenuEntry("GL_NICEST", GENERATE_MIPMAP_NICEST);
//	// utworzenie podmenu - Aspekt obrazu
//	int MenuAspect = glutCreateMenu(Menu);
//#ifdef WIN32
//	glutAddMenuEntry("Aspekt obrazu - ca�e okno", FULL_WINDOW);
//#else
//	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
//#endif
//	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);
//	// menu g��wne
//	glutCreateMenu(Menu);
//#ifdef WIN32
//	glutAddSubMenu("Filtr pomniejszaj�cy", MenuMinFilter);
//	glutAddSubMenu("GL_PERSPECTIVE_CORRECTION_HINT", PerspectiveCorrectionHint);
//	glutAddSubMenu("GL_GENERATE_MIPMAP_HINT", GenerateMipmapHint);
//	glutAddSubMenu("Aspekt obrazu", MenuAspect);
//	glutAddMenuEntry("Wyj�cie", EXIT);
//#else
//	glutAddSubMenu("Filtr pomniejszajacy", MenuMinFilter);
//	glutAddSubMenu("GL_PERSPECTIVE_CORRECTION_HINT", PerspectiveCorrectionHint);
//	glutAddSubMenu("GL_GENERATE_MIPMAP_HINT", GenerateMipmapHint);
//	glutAddSubMenu("Aspekt obrazu", MenuAspect);
//	glutAddMenuEntry("Wyjscie", EXIT);
//#endif
//	// okre�lenie przycisku myszki obs�uguj�cego menu podr�czne
//	glutAttachMenu(GLUT_RIGHT_BUTTON);
//	// utworzenie tekstur
//	GenerateTextures();
//	// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze?
//	ExtensionSetup();
//	// utworzenie list wy�wietlania
//	GenerateDisplayLists();
//	// wprowadzenie programu do obs�ugi p�tli komunikat�w
//	glutMainLoop();
//	return 0;
//}
