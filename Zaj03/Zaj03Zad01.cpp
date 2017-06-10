#include "stdafx.h"
//
//#include <cstdio>
//#include "../Library/glext.h"
//
//#include "../packages/nupengl.core.0.1.0.1/build/native/include/GL/glut.h"
//
//// sta�e do obs�ugi menu podr�cznego
//
//enum
//{
//	MAG_FILTER,     // filtr powi�kszaj�cy
//	MIN_FILTER,     // filtr pomniejszaj�cy
//	FULL_WINDOW,    // aspekt obrazu - ca�e okno
//	ASPECT_1_1,     // aspekt obrazu 1:1
//	EXIT            // wyj�cie
//};
//
//// aspekt obrazu
//
//int aspect = FULL_WINDOW;
//
//// usuni�cie definicji makr near i far
//
//#ifdef near
//#undef near
//#endif
//#ifdef far
//#undef far
//#endif
//
//// rozmiary bry�y obcinania
//
//const GLdouble left = -2.0;
//const GLdouble right = 2.0;
//const GLdouble bottom = -2.0;
//const GLdouble top = 2.0;
//const GLdouble near = 3.0;
//const GLdouble far = 7.0;
//
//// wsp�czynnik skalowania
//
//GLfloat scale = 1.05;
//
//// identyfikatory list wy�wietlania
//
//GLint RECT_LIST;
//GLint TEXTURE_256_LIST, TEXTURE_128_LIST, TEXTURE_64_LIST;
//
//// filtr powi�kszaj�cy
//
//GLint mag_filter = GL_NEAREST;
//
//// filtr pomniejszaj�cy
//
//GLint min_filter = GL_NEAREST;
//
//// funkcja generuj�ca scen� 3D
//
//void DisplayScene()
//{
//	// kolor t�a - zawarto�� bufora koloru
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//
//	// czyszczenie bufora koloru
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	// wyb�r macierzy modelowania
//	glMatrixMode(GL_MODELVIEW);
//
//	// macierz modelowania = macierz jednostkowa
//	glLoadIdentity();
//
//	// przesuni�cie uk�adu wsp�rz�dnych obiekt�w do �rodka bry�y odcinania
//	glTranslatef(0, 0, -(near + far) / 2);
//
//	// skalowanie obiektu - klawisze "+" i "-"
//	glScalef(scale, 1.0, 1.0);
//
//	// w��czenie teksturowania jednowymiarowego
//	glEnable(GL_TEXTURE_1D);
//
//	// tryb upakowania bajt�w danych tekstury
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	// filtr powi�kszaj�cy
//	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, mag_filter);
//
//	// filtr pomniejszaj�cy
//	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, min_filter);
//
//	// usunui�cie b��d�w przy renderingu brzegu tekstury
//	if (mag_filter == GL_LINEAR)
//		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//
//	// wy�wietlenie tekstur
//	glCallList(TEXTURE_256_LIST);
//	glCallList(TEXTURE_128_LIST);
//	glCallList(TEXTURE_64_LIST);
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
//			glFrustum(left, right, bottom*height / width, top*height / width, near, far);
//		else
//
//			// szeroko�? okna wi�ksza lub r�wna wysoko�ci okna
//			if (width >= height && height > 0)
//				glFrustum(left*width / height, right*width / height, bottom, top, near, far);
//	}
//	else
//		glFrustum(left, right, bottom, top, near, far);
//
//	// generowanie sceny 3D
//	DisplayScene();
//}
//
//// obs�uga klawiatury
//
//void Keyboard(unsigned char key, int x, int y)
//{
//	// klawisz +
//	if (key == '+')
//		scale += 0.05;
//	else
//
//		// klawisz -
//		if (key == '-' && scale > 0.05)
//			scale -= 0.05;
//
//	// narysowanie sceny
//	DisplayScene();
//}
//
//// obs�uga menu podr�cznego
//
//void Menu(int value)
//{
//	switch (value)
//	{
//		// filtr powi�kszaj�cy: GL_NEAREST/GL_LINEAR
//	case MAG_FILTER:
//		if (mag_filter == GL_NEAREST)
//			mag_filter = GL_LINEAR;
//		else
//			mag_filter = GL_NEAREST;
//		DisplayScene();
//		break;
//
//		// filtr pomniejszaj�cy: GL_NEAREST/GL_LINEAR
//	case MIN_FILTER:
//		if (min_filter == GL_NEAREST)
//			min_filter = GL_LINEAR;
//		else
//			min_filter = GL_NEAREST;
//		DisplayScene();
//		break;
//
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
//// utworzenie list wy�wietlania
//
//void GenerateDisplayLists()
//{
//	// generowanie identyfikatora listy wy�wietlania
//	RECT_LIST = glGenLists(1);
//
//	// lista wy�wietlania - prostok�t
//	glNewList(RECT_LIST, GL_COMPILE);
//
//	// na�o?enie tekstury na prostok�t
//	glBegin(GL_QUADS);
//	glTexCoord1f(1.0);
//	glVertex2f(1.5, 0.7);
//	glTexCoord1f(0.0);
//	glVertex2f(-1.5, 0.7);
//	glTexCoord1f(0.0);
//	glVertex2f(-1.5, -0.7);
//	glTexCoord1f(1.0);
//	glVertex2f(1.5, -0.7);
//	glEnd();
//
//	// koniec listy wy�wietlania
//	glEndList();
//
//	// sprawdzenie czy implementacja biblioteki obs�uguje tekstury o wymiarze 256
//	GLint size;
//	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
//	if (size < 256)
//	{
//		printf("Rozmiar tekstur mniejszy od 256");
//		exit(0);
//	}
//
//	// dane tekstury
//	GLubyte texture[256 * 3];
//
//	// przygotowanie danych tekstury RGB
//	for (int i = 0; i < 256; i++)
//	{
//		texture[3 * i + 0] = i;
//		texture[3 * i + 1] = i;
//		texture[3 * i + 2] = i;
//	}
//
//	// generowanie identyfikatora listy wy�wietlania
//	TEXTURE_256_LIST = glGenLists(1);
//
//	// lista wy�wietlania - tekstura o szeroko�ci 256 tekseli
//	glNewList(TEXTURE_256_LIST, GL_COMPILE);
//
//	// definiowanie tekstury
//	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
//
//	// od�o?enie macierzy modelowania na stos
//	glPushMatrix();
//
//	// przesuni�cie prostok�ta do g�ry o dwie jednostki
//	glTranslatef(0.0, 2.0, 0.0);
//
//	// na�o?enie tekstury na prostok�t
//	glCallList(RECT_LIST);
//
//	// zdj�cie macierzy modelowania ze stosu
//	glPopMatrix();
//
//	// koniec listy wy�wietlania
//	glEndList();
//
//	//  przygotowanie danych tekstury LUMINANCE
//	for (int i = 0; i < 128; i++)
//	{
//		texture[i] = i * 2;
//	}
//
//	// generowanie identyfikatora listy wy�wietlania
//	TEXTURE_128_LIST = glGenLists(1);
//
//	// lista wy�wietlania - tekstura o szeroko�ci 128 tekseli
//	glNewList(TEXTURE_128_LIST, GL_COMPILE);
//
//	// definiowanie tekstury
//	glTexImage1D(GL_TEXTURE_1D, 0, GL_LUMINANCE, 128, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, texture);
//
//	// na�o?enie tekstury na prostok�t
//	glCallList(RECT_LIST);
//
//	// koniec listy wy�wietlania
//	glEndList();
//
//	// przygotowanie danych tekstury INTENSITY
//	for (int i = 0; i < 64; i++)
//	{
//		texture[3 * i] = i * 4;
//	}
//
//	// generowanie identyfikatora listy wy�wietlania
//	TEXTURE_64_LIST = glGenLists(1);
//
//	// lista wy�wietlania - tekstura o szeroko�ci 64 tekseli
//	glNewList(TEXTURE_64_LIST, GL_COMPILE);
//
//	// definiowanie tekstury
//	glTexImage1D(GL_TEXTURE_1D, 0, GL_INTENSITY, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
//
//	// od�o?enie macierzy modelowania na stos
//	glPushMatrix();
//
//	// przesuni�cie prostok�ta do do�u o dwie jednostki
//	glTranslatef(0.0, -2.0, 0.0);
//
//	// na�o?enie tekstury na prostok�t
//	glCallList(RECT_LIST);
//
//	// zdj�cie macierzy modelowania ze stosu
//	glPopMatrix();
//
//	// koniec listy wy�wietlania
//	glEndList();
//}
//
//// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze?
//
//void ExtensionSetup()
//{
//	// pobranie numeru wersji biblioteki OpenGL
//	const char *version = (char*)glGetString(GL_VERSION);
//
//	// odczyt wersji OpenGL
//	int major = 0, minor = 0;
//	if (sscanf_s(version, "%d.%d", &major, &minor) != 2)
//	{
//#ifdef WIN32
//		printf("B��dny format wersji OpenGL\n");
//#else
//
//		printf("Bledny format wersji OpenGL\n");
//#endif
//
//		exit(0);
//	}
//
//	// sprawdzenie czy jest co najmniej wersja 1.2 OpenGL lub
//	// czy jest obs�ugiwane rozszerzenie GL_SGIS_texture_edge_clamp
//	if (!(major > 1 || minor >= 2) &&
//		!glutExtensionSupported("GL_SGIS_texture_edge_clamp"))
//	{
//		printf("Brak rozszerzenia GL_SGIS_texture_edge_clamp!\n");
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
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//
//	// rozmiary g��wnego okna programu
//	glutInitWindowSize(500, 500);
//
//	// utworzenie g��wnego okna programu
//	glutCreateWindow("Tekstura 1D");
//
//	// do��czenie funkcji generuj�cej scen� 3D
//	glutDisplayFunc(DisplayScene);
//
//	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
//	glutReshapeFunc(Reshape);
//
//	// do��czenie funkcji obs�ugi klawiatury
//	glutKeyboardFunc(Keyboard);
//
//	// utworzenie podmenu - Aspekt obrazu
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
//
//#ifdef WIN32
//
//	glutAddMenuEntry("Filtr powi�kszaj�cy: GL_NEAREST/GL_LINEAR", MAG_FILTER);
//	glutAddMenuEntry("Filtr pomniejszaj�cy: GL_NEAREST/GL_LINEAR", MIN_FILTER);
//	glutAddSubMenu("Aspekt obrazu", MenuAspect);
//	glutAddMenuEntry("Wyj�cie", EXIT);
//#else
//
//	glutAddMenuEntry("Filtr powiekszajacy: GL_NEAREST/GL_LINEAR", MAG_FILTER);
//	glutAddMenuEntry("Filtr pomniejszajacy: GL_NEAREST/GL_LINEAR", MIN_FILTER);
//	glutAddSubMenu("Aspekt obrazu", MenuAspect);
//	glutAddMenuEntry("Wyjscie", EXIT);
//#endif
//
//	// okre�lenie przycisku myszki obs�uguj�cego menu podr�czne
//	glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//	// utworzenie list wy�wietlania
//	GenerateDisplayLists();
//
//	// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze?
//	ExtensionSetup();
//
//	// wprowadzenie programu do obs�ugi p�tli komunikat�w
//	glutMainLoop();
//	return 0;
//}
