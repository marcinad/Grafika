#include "stdafx.h"

#include "../packages/nupengl.core.0.1.0.1/build/native/include/GL/glut.h"
#ifndef WIN32
#define GLX_GLXEXT_LEGACY
#include <GL/glx.h>
#define wglGetProcAddress glXGetProcAddressARB
#endif


#include "../Library/glext.h"
#include <stdlib.h>
#include <stdio.h>
#include "../Library/colors.h"
#include "../Library/targa.h"
#include <GLFW/glfw3.h>


// wska?nik na funkcj� glWindowPos2i

PFNGLWINDOWPOS2IPROC glWindowPos2i = NULL;

// sta�e do obs�ugi menu podr�cznego

enum
{
	VENUS_TEX,      // Wenus
	EARTH_TEX,      // Ziemia
	MARS_TEX,       // Mars
	FULL_WINDOW,    // aspekt obrazu - ca�e okno
	ASPECT_1_1,     // aspekt obrazu 1:1
	EXIT            // wyj�cie
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

GLfloat rotatex = 270.0;
GLfloat rotatez = 0.0;

// wska?nik naci�ni�cia lewego przycisku myszki

int button_state = GLUT_UP;

// po�o�enie kursora myszki

int button_x, button_y;

// wsp�czynnik skalowania

GLfloat scale = 1.5;

// identyfikatory tekstur

GLuint VENUS, EARTH, MARS;

// identyfikator bie��cej tekstury

GLuint texture;

// filtr pomniejszaj�cy

GLint min_filter = GL_LINEAR_MIPMAP_LINEAR;

// funkcja rysuj�ca napis w wybranym miejscu
// (wersja korzystaj�ca z funkcji glWindowPos2i)

void DrawString(GLint x, GLint y, char *string)
{
	// po�o�enie napisu
	glWindowPos2i(x, y);

	// wy�wietlenie napisu
	int len = strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
}

// funkcja generuj�ca scen� 3D

void DisplayScene()
{
	// kolor t�a - zawarto�� bufora koloru
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
	glRotatef(rotatez, 0.0, 0.0, 1.0);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);

	// w��czenie testu bufora g��boko�ci
	glEnable(GL_DEPTH_TEST);

	// w��czenie teksturowania dwuwymiarowego
	glEnable(GL_TEXTURE_2D);

	// filtr powi�kszaj�cy
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// filtr pomniejszaj�cy
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);

	// dowi�zanie wybranej tekstury
	glBindTexture(GL_TEXTURE_2D, texture);

	// ustawienie paramet�w �rodowiska tekstur
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// utworzenie kwadryki
	GLUquadricObj *quadobj = gluNewQuadric();

	// styl (wygl�d) generowanej kwadryki
	gluQuadricDrawStyle(quadobj, GLU_FILL);

	// spos�b generacji wektor�w normalnych
	gluQuadricNormals(quadobj, GLU_SMOOTH);

	// na�o�enie tekstury na kwadryk�
	gluQuadricTexture(quadobj, GL_TRUE);

	// narysowanie kuli
	gluSphere(quadobj, 1.0, 30, 30);

	// usuni�cie kwadryki
	gluDeleteQuadric(quadobj);

	// wy��czenie teksturowania dwuwymiarowego
	glDisable(GL_TEXTURE_2D);

	// informacje o wybranych parametrach bie��cej tekstury
	char string[200];
	GLfloat var;
	glColor3fv(Black);

	// warto�� priorytetu tekstury
	glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_PRIORITY, &var);
	sprintf_s(string, "GL_TEXTURE_PRIORITY = %f", var);
	DrawString(2, 2, string);

	// czy tekstura jest rezydentna
	glGetTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_RESIDENT, &var);
	if (var == GL_FALSE)
		strcpy_s(string, "GL_TEXTURE_RESIDENT = GL_FALSE");
	else
		strcpy_s(string, "GL_TEXTURE_RESIDENT = GL_TRUE");
	DrawString(2, 16, string);

	// szeroko�� tekstury (poziom 0)
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &var);
	sprintf_s(string, "GL_TEXTURE_WIDTH = %f", var);
	DrawString(2, 30, string);

	// wysoko�� tekstury (poziom 0)
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &var);
	sprintf_s(string, "GL_TEXTURE_HEIGHT = %f", var);
	DrawString(2, 46, string);

	// skierowanie polece? do wykonania
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
		// wysoko�� okna wi�ksza od wysoko�ci okna
		if (width < height && width > 0)
			glFrustum(left, right, bottom*height / width, top*height / width, near, far);
		else

			// szeroko�� okna wi�ksza lub r�wna wysoko�ci okna
			if (width >= height && height > 0)
				glFrustum(left*width / height, right*width / height, bottom, top, near, far);
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

		// zapami�tanie po�o�enia kursora myszki
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
		rotatez += 30 * (right - left) / glutGet(GLUT_WINDOW_WIDTH) * (x - button_x);
		button_x = x;
		rotatex -= 30 * (top - bottom) / glutGet(GLUT_WINDOW_HEIGHT) * (button_y - y);
		button_y = y;
		glutPostRedisplay();
	}
}

// obs�uga menu podr�cznego

void Menu(int value)
{
	switch (value)
	{
		// Wenus
	case VENUS_TEX:
		texture = VENUS;
		DisplayScene();
		break;

		// Ziemia
	case EARTH_TEX:
		texture = EARTH;
		DisplayScene();
		break;

		// Mars
	case MARS_TEX:
		texture = MARS;
		DisplayScene();
		break;

		// filtr pomniejszaj�cy
	case GL_NEAREST_MIPMAP_NEAREST:
	case GL_NEAREST_MIPMAP_LINEAR:
	case GL_LINEAR_MIPMAP_NEAREST:
	case GL_LINEAR_MIPMAP_LINEAR:
		min_filter = value;
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

// utworzenie tekstur

void GenerateTextures()
{
	// zmienne u�yte przy obs�udze plik�w TARGA
	GLsizei width, height;
	GLenum format, type;
	GLvoid *pixels;

	// tryb upakowania bajt�w danych tekstury
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	
	// wczytanie tekstury Marsa utworzonej ze zdj�� sond Viking
	// plik: http://maps.jpl.nasa.gov/pix/mar0kuu2.tif
	
	GLboolean error = load_targa("mars.tga", width, height, format, type, pixels);

	// b��d odczytu pliku
	if (error == GL_FALSE)
	{
		printf("Niepoprawny odczyt pliku mar0kuu2.tga");
		exit(0);
	}

	// utworzenie identyfikatora tekstury
	glGenTextures(1, &MARS);

	// dowi�zanie stanu tekstury
	glBindTexture(GL_TEXTURE_2D, MARS);

	// utworzenie tekstury wraz z mipmapami
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, format, type, pixels);

	// porz�dki
	delete[](unsigned char*)pixels;

	// identyfikator bie��cej tekstury
	texture = MARS;
}

// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze?

void ExtensionSetup()
{
	// pobranie numeru wersji biblioteki OpenGL
	const char *version = (char*)glGetString(GL_VERSION);

	// odczyt wersji OpenGL
	int major = 0, minor = 0;
	if (sscanf_s(version, "%d.%d", &major, &minor) != 2)
	{
#ifdef WIN32
		printf("B��dny format wersji OpenGL\n");
#else

		printf("Bledny format wersji OpenGL\n");
#endif

		exit(0);
	}

	// sprawdzenie czy jest co najmniej wersja 1.4
	if (major > 1 || minor >= 4)
	{
		// pobranie wska?nika wybranej funkcji OpenGL 1.4
		glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress("glWindowPos2i");
	}
	else
		// sprawdzenie czy jest obs�ugiwane rozszerzenie ARB_window_pos
		if (glutExtensionSupported("GL_ARB_window_pos"))
		{
			// pobranie wska?nika wybranej funkcji rozszerzenia ARB_window_pos
			glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress("glWindowPos2iARB");
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
	glutCreateWindow("Tekstura 2D");

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

	// utworzenie podmenu - Planeta
	int MenuPlanet = glutCreateMenu(Menu);
	glutAddMenuEntry("Wenus", VENUS_TEX);
	glutAddMenuEntry("Ziemia", EARTH_TEX);
	glutAddMenuEntry("Mars", MARS_TEX);

	// utworzenie podmenu - Filtr pomniejszaj�cy
	int MenuMinFilter = glutCreateMenu(Menu);
	glutAddMenuEntry("GL_NEAREST_MIPMAP_NEAREST", GL_NEAREST_MIPMAP_NEAREST);
	glutAddMenuEntry("GL_NEAREST_MIPMAP_LINEAR", GL_NEAREST_MIPMAP_LINEAR);
	glutAddMenuEntry("GL_LINEAR_MIPMAP_NEAREST", GL_LINEAR_MIPMAP_NEAREST);
	glutAddMenuEntry("GL_LINEAR_MIPMAP_LINEAR", GL_LINEAR_MIPMAP_LINEAR);

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
	glutAddSubMenu("Planeta", MenuPlanet);

#ifdef WIN32

	glutAddSubMenu("Filtr pomniejszaj�cy", MenuMinFilter);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddMenuEntry("Wyj�cie", EXIT);
#else

	glutAddSubMenu("Filtr pomniejszajacy", MenuMinFilter);
	glutAddSubMenu("Aspekt obrazu", MenuAspect);
	glutAddMenuEntry("Wyjscie", EXIT);
#endif

	// okre�lenie przycisku myszki obs�uguj�cego menu podr�czne
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// utworzenie tekstur
	GenerateTextures();

	// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze?
	ExtensionSetup();

	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();
	return 0;
}
