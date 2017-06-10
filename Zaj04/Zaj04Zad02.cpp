#include "stdafx.h"
#include <GL/glut.h>
#include "../Library/glext.h"
#ifndef WIN32
#define GLX_GLXEXT_LEGACY
#include <GL/glx.h>
#define wglGetProcAddress glXGetProcAddressARB
#endif
#include <stdlib.h>
#include <stdio.h>
#include "../Library/colors.h"
#include "../Zaj04/targa.h"
// wska�nik na funkcj� glWindowPos2i
PFNGLWINDOWPOS2IPROC glWindowPos2i = NULL;
// sta�e do obs�ugi menu podr�cznego
enum
{
	FULL_WINDOW, // aspekt obrazu - ca�e okno
	ASPECT_1_1, // aspekt obrazu 1:1
	EXIT // wyj�cie
};
// aspekt obrazu
int aspect = FULL_WINDOW;
// usuni�cie definicji makr near i far
#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif
// rozmiary bry�y obcinania
const GLdouble left = -2.0;
const GLdouble right = 2.0;
const GLdouble bottom = -2.0;
const GLdouble top = 2.0;
const GLdouble near = 3.0;
const GLdouble far = 7.0;
// k�ty obrotu
GLfloat rotatex = 0.0;
GLfloat rotatey = 0.0;
// wska�nik naci�ni�cia lewego przycisku myszki
int button_state = GLUT_UP;
// po�o?enie kursora myszki
int button_x, button_y;
// wsp�czynnik skalowania
GLfloat scale = 1.5;
// identyfikatory tekstur
GLuint GRASS, TREE;
// identyfikatory list wy�wietlania
GLint GRASS_LIST, TREE_LIST;
// w��czenie/wy��czenie
bool alpha_test = true;
bool blend = false;
// funkcja rysuj�ca napis w wybranym miejscu
// (wersja korzystaj�ca z funkcji glWindowPos2i)
void DrawString(GLint x, GLint y, char *string)
{
	// po�o?enie napisu
	glWindowPos2i(x, y);
	// wy�wietlenie napisu
	int len = strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
}
// funkcja generuj�ca scen� 3D
void DisplayScene()
{
	// kolor t�a - zawarto�? bufora koloru
	glClearColor(1.0, 1.0, 1.0, 1.0);
	// czyszczenie bufora koloru i bufora g��boko�ci
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// wyb�r macierzy modelowania
	glMatrixMode(GL_MODELVIEW);
	// macierz modelowania = macierz jednostkowa
	glLoadIdentity();
	// przesuni�cie uk�adu wsp�rz�dnych obiekt�w do �rodka bry�y odcinania
	glTranslatef(0.0, 0.0, -(near + far) / 2);
	// obroty obiektu
	glRotatef(rotatex, 1.0, 0.0, 0.0);
	glRotatef(rotatey, 0.0, 1.0, 0.0);
	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);
	// w��czenie testu bufora g��boko�ci
	glEnable(GL_DEPTH_TEST);
	// w��czenie teksturowania dwuwymiarowego
	glEnable(GL_TEXTURE_2D);
	// filtr powi�kszaj�cy
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// filtr pomniejszaj�cy
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// wskaz�wki do korekcji perspektywy przy renderingu tekstur
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// ustawienie paramet�w �rodowiska tekstur
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	// w��czenie/wy��czenie testowania kana�u alfa
	if (alpha_test == GL_TRUE)
	{
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.5);
	}
	else
		glDisable(GL_ALPHA_TEST);
	// w��czenie/wy��czenie mieszania kolor�w
	if (blend == GL_TRUE)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
		glDisable(GL_BLEND);
	// rysowanie trawy
	glBindTexture(GL_TEXTURE_2D, GRASS);
	glPushMatrix();
	glTranslatef(0.0, -0.5, 0.0);
	glCallList(GRASS_LIST);
	glPopMatrix();
	// rysowanie trzech drzew
	glBindTexture(GL_TEXTURE_2D, TREE);
	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	glCallList(TREE_LIST);
	glTranslatef(1.0, 0.0, 0.5);
	glCallList(TREE_LIST);
	glTranslatef(1.0, 0.0, 0.5);
	glCallList(TREE_LIST);
	glPopMatrix();
	// wy��czenie teksturowania dwuwymiarowego
	glDisable(GL_TEXTURE_2D);
	// wy�wietlenie wybranych informacje
	char string[200];
	GLboolean var;
	glColor3fv(Black);
	// pobranie inforacji o w��czeniu testowania kana�u alfa
	glGetBooleanv(GL_ALPHA_TEST, &var);
	if (var == GL_TRUE)
		strcpy(string, "GL_ALPHA_TEST = GL_TRUE");
	else
		strcpy(string, "GL_ALPHA_TEST = GL_FALSE");
	DrawString(2, glutGet(GLUT_WINDOW_HEIGHT) - 17, string);
	// pobranie informacji o w��czeniu mieszania kolor�w
	glGetBooleanv(GL_BLEND, &var);
	if (var == GL_TRUE)
		strcpy(string, "GL_BLEND = GL_TRUE");
	else
		strcpy(string, "GL_BLEND = GL_FALSE");
	DrawString(2, glutGet(GLUT_WINDOW_HEIGHT) - 33, string);
	// skierowanie polece� do wykonania
	glFlush();
	// zamiana bufor�w koloru
	glutSwapBuffers();
}
// zmiana wielko�ci okna
void Reshape(int width, int height)
{
	// obszar renderingu - ca�e okno
	glViewport(0, 0, width, height);
	// wyb�r macierzy rzutowania
	glMatrixMode(GL_PROJECTION);
	// macierz rzutowania = macierz jednostkowa
	glLoadIdentity();
	// parametry bry�y obcinania
	if (aspect == ASPECT_1_1)
	{
		// wysoko�? okna wi�ksza od wysoko�ci okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom*height / width, top*height / width, near, far);
		else
			// szeroko�? okna wi�ksza lub r�wna wysoko�ci okna
			if (width >= height && height > 0)
				glFrustum(left*width / height, right*width / height, bottom, top, near,
					far);
	}
	else
		glFrustum(left, right, bottom, top, near, far);
	// generowanie sceny 3D
	DisplayScene();
}
// obs�uga klawiatury
void Keyboard(unsigned char key, int x, int y)
{
	// klawisz +
	if (key == '+')
		scale += 0.05;
	else
		// klawisz -
		if (key == '-' && scale > 0.05)
			scale -= 0.05;
	// narysowanie sceny
	DisplayScene();
}
// obs�uga przycisk�w myszki
void MouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		// zapami�tanie stanu lewego przycisku myszki
		button_state = state;
		// zapami�tanie po�o?enia kursora myszki
		if (state == GLUT_DOWN)
		{
			button_x = x;
			button_y = y;
		}
	}
}
// obs�uga ruchu kursora myszki
void MouseMotion(int x, int y)
{
	if (button_state == GLUT_DOWN)
	{
		rotatey += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}
// utworzenie tekstur
void GenerateTextures()
{
	// zmienne u?yte przy obs�udze plik�w TARGA
	GLsizei width, height;
	GLenum format, type;
	GLvoid *pixels;
	// tryb upakowania bajt�w danych tekstury
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// wczytanie tekstury grass_color.tga
	GLboolean error = load_targa("grass.tga", width, height, format, type, pixels);
	// b��d odczytu pliku
	if (error == GL_FALSE)
	{
		printf("Niepoprawny odczyt pliku grass.tga");
		exit(0);
	}
	// utworzenie identyfikatora tekstury
	glGenTextures(1, &GRASS);
	// dowi�zanie stanu tekstury
	glBindTexture(GL_TEXTURE_2D, GRASS);
	// w��czenie automatycznego generowania mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	// definiowanie tekstury (z mipmapami)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, type, pixels);
	// porz�dki
	delete[](unsigned char*)pixels;
	// wczytanie tekstury branch.tga
	error = load_targa("cherry.tga", width, height, format, type, pixels);
	// b��d odczytu pliku
	if (error == GL_FALSE)
	{
		printf("Niepoprawny odczyt pliku cherry.tga");
		exit(0);
	}
	// utworzenie identyfikatora tekstury
	glGenTextures(1, &TREE);
	// dowi�zanie stanu tekstury
	glBindTexture(GL_TEXTURE_2D, TREE);
	// w��czenie automatycznego generowania mipmap
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	// definiowanie tekstury (z mipmapami)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, type, pixels);
	// porz�dki
	delete[](unsigned char*)pixels;
}
// obs�uga menu podr�cznego
void Menu(int value)
{
	switch (value)
	{
		// test kana�u alfa: w��cz/wy��cz
	case GL_ALPHA_TEST:
		alpha_test = !alpha_test;
		DisplayScene();
		break;
		// mieszanie kolor�w: w��cz/wy��cz
	case GL_BLEND:
		blend = !blend;
		DisplayScene();
		break;
		// obszar renderingu - ca�e okno
	case FULL_WINDOW:
		aspect = FULL_WINDOW;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
		// obszar renderingu - aspekt 1:1
	case ASPECT_1_1:
		aspect = ASPECT_1_1;
		Reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		break;
		// wyj�cie
	case EXIT:
		exit(0);
	}
}
// utworzenie list wy�wietlania
void GenerateDisplayLists()
{
	// generowanie identyfikatora pierwszej listy wy�wietlania
	GRASS_LIST = glGenLists(1);
	// pierwsza lista wy�wietlania - trawa
	glNewList(GRASS_LIST, GL_COMPILE);
	// czworok�t
	glBegin(GL_QUADS);
	glTexCoord2f(16.0, 0.0);
	glVertex3f(-8.0, 0.0, -8.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-8.0, 0.0, 8.0);
	glTexCoord2f(0.0, 16.0);
	glVertex3f(8.0, 0.0, 8.0);
	glTexCoord2f(16.0, 16.0);
	glVertex3f(8.0, 0.0, -8.0);
	glEnd();
	// koniec pierwszej listy wy�wietlania
	glEndList();
	// generowanie identyfikatora drugiej listy wy�wietlania
	TREE_LIST = glGenLists(1);
	// druga lista wy�wietlania - drzewo
	glNewList(TREE_LIST, GL_COMPILE);
	// dwa tr�jk�ty
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0, 1.0, 0.0);
	glEnd();
	// koniec drugiej listy wy�wietlania
	glEndList();
}
// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze�
void ExtensionSetup()
{
	// pobranie numeru wersji biblioteki OpenGL
	const char *version = (char*)glGetString(GL_VERSION);
	// odczyt wersji OpenGL
	int major = 0, minor = 0;
	if (sscanf(version, "%d.%d", &major, &minor) != 2)
	{
#ifdef WIN32
		printf("B��dny format wersji OpenGL\n");
#else
		printf("Bledny format wersji OpenGL\n");
#endif
		exit(0);
	}
	// sprawdzenie czy jest co najmniej wersja 1.4 OpenGL lub
	// czy jest obs�ugiwane rozszerzenie GL_SGIS_generate_mipmap
	if (!(major > 1 || minor >= 4) &&
		!glutExtensionSupported("GL_SGIS_generate_mipmap"))
	{
		printf("Brak rozszerzenia GL_SGIS_generate_mipmap!\n");
		exit(0);
	}
	// sprawdzenie czy jest co najmniej wersja 1.4
	if (major > 1 || minor >= 4)
	{
		// pobranie wska�nika wybranej funkcji OpenGL 1.4
		glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress("glWindowPos2i");
	}
	else
		// sprawdzenie czy jest obs�ugiwane rozszerzenie ARB_window_pos
		if (glutExtensionSupported("GL_ARB_window_pos"))
		{
			// pobranie wska�nika wybranej funkcji rozszerzenia ARB_window_pos
			glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress
			("glWindowPos2iARB");
		}
		else
		{
			printf("Brak rozszerzenia ARB_window_pos!\n");
			exit(0);
		}
}
int main(int argc, char *argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);
	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	// rozmiary g��wnego okna programu
	glutInitWindowSize(500, 500);
	// utworzenie g��wnego okna programu
	glutCreateWindow("Tekstura alfa");
	// do��czenie funkcji generuj�cej scen� 3D
	glutDisplayFunc(DisplayScene);
	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(Reshape);
	// do��czenie funkcji obs�ugi klawiatury
	glutKeyboardFunc(Keyboard);
	// obs�uga przycisk�w myszki
	glutMouseFunc(MouseButton);
	// obs�uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);
	// utworzenie podmenu - Aspekt obrazu
	int MenuAspect = glutCreateMenu(Menu);
#ifdef WIN32
	glutAddMenuEntry("Aspekt obrazu - ca�e okno", FULL_WINDOW);
#else
	glutAddMenuEntry("Aspekt obrazu - cale okno", FULL_WINDOW);
#endif
	glutAddMenuEntry("Aspekt obrazu 1:1", ASPECT_1_1);
	// menu g��wne
	glutCreateMenu(Menu);
#ifdef WIN32
	glutAddMenuEntry("Test kana�u alfa: w��cz/wy��cz", GL_ALPHA_TEST);
	glutAddMenuEntry("Mieszanie kolor�w: w��cz/wy��cz", GL_BLEND);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddMenuEntry("Wyj�cie", EXIT);
#else
	glutAddMenuEntry("Test kanalu alfa: wlacz/wylacz", GL_ALPHA_TEST);
	glutAddMenuEntry("Mieszanie kolorow: wlacz/wylacz", GL_BLEND);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddMenuEntry("Wyjscie", EXIT);
#endif
	// okre�lenie przycisku myszki obs�uguj�cego menu podr�czne
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	// utworzenie tekstur
	GenerateTextures();
	// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze�
	ExtensionSetup();
	// utworzenie list wy�wietlania
	GenerateDisplayLists();
	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	return 0;
}