#include "stdafx.h"
//
//#ifndef WIN32
//#define GLX_GLXEXT_LEGACY
//#define wglGetProcAddress glXGetProcAddressARB
//#endif
//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//
//#include "../packages/nupengl.core.0.1.0.1/build/native/include/GL/glut.h"
//#include "../Library/glext.h"
//#include "../Library/materials.h"
//#include "../Library/colors.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include "../Library/master.h"
//
//#include <GL/GL.h>
//#include <GL/GLU.h>
//#include "../packages/nupengl.core.0.1.0.1/build/native/include/GL/freeglut.h"
////#include <GL/glx.h>
//
//// wska�nik na funkcj� glWindowPos2i
//
//PFNGLWINDOWPOS2IPROC glWindowPos2i = NULL;
//
//// sta�e do obs�ugi menu podr�cznego
//
//enum
//{
//	// obiekty
//	SPHERE,               // kula
//	TEAPOT,               // czajnik
//	CONE,                 // sto�ek
//	TORUS,                // torus
//	CUBE,                 // sze�cian
//	DODECAHEDRON,         // dwunasto�cian
//	OCTAHEDRON,           // o�mio�cian
//	TETRAHEDRON,          // czworo�cian
//	ICOSAHEDRON,          // dwudziesto�cian
//
//						  // materia�y
//						  BRASS,                // mosi�dz
//						  BRONZE,               // br�z
//						  POLISHED_BRONZE,      // polerowany br�z
//						  CHROME,               // chrom
//						  COPPER,               // mied�
//						  POLISHED_COPPER,      // polerowana mied�
//						  GOLD,                 // z�oto
//						  POLISHED_GOLD,        // polerowane z�oto
//						  PEWTER,               // grafit (cyna z o�owiem)
//						  SILVER,               // srebro
//						  POLISHED_SILVER,      // polerowane srebro
//						  EMERALD,              // szmaragd
//						  JADE,                 // jadeit
//						  OBSIDIAN,             // obsydian
//						  PEARL,                // per�a
//						  RUBY,                 // rubin
//						  TURQUOISE,            // turkus
//						  BLACK_PLASTIC,        // czarny plastik
//						  BLACK_RUBBER,         // czarna guma
//
//												// obszar renderingu
//												FULL_WINDOW,          // aspekt obrazu - ca�e okno
//												ASPECT_1_1,           // aspekt obrazu 1:1
//												EXIT                  // wyj�cie
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
//// k�ty obrotu obiektu
//
//GLfloat rotatex = 0.0;
//GLfloat rotatey = 0.0;
//
//// wska�nik naci�ni�cia lewego przycisku myszki
//
//int button_state = GLUT_UP;
//
//// po�o�enie kursora myszki
//
//int button_x, button_y;
//
//// wsp�czynnik skalowania
//
//GLfloat scale = 1.0;
//
//// w�a�ciwo�ci materia�u - domy�lnie mosi�dz
//
//const GLfloat *ambient = BrassAmbient;
//const GLfloat *diffuse = BrassDiffuse;
//const GLfloat *specular = BrassSpecular;
//GLfloat shininess = BrassShininess;
//
//// wy�wietlany obiekt 3D
//
//int object = SPHERE;
//
//// kierunek �r�d�a �wiat�a
//
//GLfloat light_position[4] =
//{
//	0.0,0.0,2.0,0.0
//};
//
//// k�ty obrotu kierunku �r�d�a �wiat�a
//
//GLfloat light_rotatex = 0.0;
//GLfloat light_rotatey = 0.0;
//
//// funkcja rysuj�ca napis w wybranym miejscu
//// (wersja korzystaj�ca z funkcji glWindowPos2i)
//
//void DrawString(GLint x, GLint y, char *string)
//{
//	// po�o�enie napisu
//	glWindowPos2i(x, y);
//
//	// wy�wietlenie napisu
//	int len = strlen(string);
//	for (int i = 0; i < len; i++)
//		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
//}
//// funkcja generuj�ca scen� 3D
//
//void DisplayScene()
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
//	// w��czenie testu bufora g��boko�ci
//	glEnable(GL_DEPTH_TEST);
//
//	// w��czenie o�wietlenia
//	glEnable(GL_LIGHTING);
//
//	// w��czenie �wiat�a GL_LIGHT0
//	glEnable(GL_LIGHT0);
//
//	// w��czenie automatycznej normalizacji wektor�w normalnych
//	glEnable(GL_NORMALIZE);
//
//	// przesuni�cie uk�adu wsp�rz�dnych obiektu do �rodka bry�y odcinania
//	glTranslatef(0, 0, -(near + far) / 2);
//
//	// obroty obiektu
//	glRotatef(rotatex, 1.0, 0, 0);
//	glRotatef(rotatey, 0, 1.0, 0);
//
//	// skalowanie obiektu - klawisze "+" i "-"
//	glScalef(scale, scale, scale);
//
//	// w�a�ciwo�ci materia�u
//	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
//	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
//
//	// zmiana kierunku �r�d�a �wiat�a jest wykonywana niezale�nie
//	// od obrot�w obiektu, st�d od�o�enie na stos macierzy modelowania
//	glPushMatrix();
//
//	// macierz modelowania = macierz jednostkowa
//	glLoadIdentity();
//
//	// obroty kierunku �r�d�a �wiat�a - klawisze kursora
//	glRotatef(light_rotatex, 1.0, 0, 0);
//	glRotatef(light_rotatey, 0, 1.0, 0);
//
//	// ustalenie kierunku �r�d�a �wiat�a
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//
//	// przywr�cenie pierwotnej macierzy modelowania
//	glPopMatrix();
//
//	// rysowanie wybranego obiektu 3D
//	switch (object)
//	{
//		// kula
//	case SPHERE:
//		glutSolidSphere(1.0, 50, 40);
//		break;
//
//		// czajnik
//	case TEAPOT:
//		glutSolidTeapot(1);
//		break;
//
//		// sto�ek
//	case CONE:
//		glutSolidCone(1, 1, 50, 40);
//		break;
//
//		// torus
//	case TORUS:
//		glutSolidTorus(0.3, 1, 40, 50);
//		break;
//
//		// sze�cian
//	case CUBE:
//		glutSolidCube(1);
//		break;
//
//		// dwunasto�cian
//	case DODECAHEDRON:
//		glutSolidDodecahedron();
//		break;
//
//		// o�mio�cian
//	case OCTAHEDRON:
//		glutSolidOctahedron();
//		break;
//
//		// czworo�cian
//	case TETRAHEDRON:
//		glutSolidTetrahedron();
//		break;
//
//		// dwudziesto�cian
//	case ICOSAHEDRON:
//		glutSolidIcosahedron();
//		break;
//	}
//
//	// informacje o modyfikowanych warto�ciach
//	// parametr�w �r�d�a �wiata�a GL_LIGHT0
//	char string[200];
//	GLfloat vec[4];
//	glColor3fv(Black);
//
//	// kierunek �r�d�a �wiat�a
//	glGetLightfv(GL_LIGHT0, GL_POSITION, vec);
//	sprintf_s(string, "GL_POSITION = (%f,%f,%f,%f)", vec[0], vec[1], vec[2], vec[3]);
//	DrawString(2, 2, string);
//
//	// k�ty obrotu kierunku �r�d�a �wiat�a
//	sprintf_s(string, "light_rotatex = %f", light_rotatex);
//	DrawString(2, 16, string);
//	sprintf_s(string, "light_rotatey = %f", light_rotatey);
//	DrawString(2, 30, string);
//
//	// skierowanie polece� do wykonania
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
//	switch (key)
//	{
//		// klawisz "+" - powi�kszenie obiektu
//	case '+':
//		scale += 0.05;
//		break;
//
//		// klawisz "-" - zmniejszenie obiektu
//	case '-':
//		if (scale > 0.05)
//			scale -= 0.05;
//		break;
//	}
//
//	// narysowanie sceny
//	DisplayScene();
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
//		// zapami�tanie po�o�enia kursora myszki
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
//// obs�uga klawiszy funkcyjnych i klawiszy kursora
//
//void SpecialKeys(int key, int x, int y)
//{
//	switch (key)
//	{
//		// kursor w lewo
//	case GLUT_KEY_LEFT:
//		light_rotatey -= 5;
//		break;
//
//		// kursor w prawo
//	case GLUT_KEY_RIGHT:
//		light_rotatey += 5;
//		break;
//
//		// kursor w d�
//	case GLUT_KEY_DOWN:
//		light_rotatex += 5;
//		break;
//
//		// kursor w g�r�
//	case GLUT_KEY_UP:
//		light_rotatex -= 5;
//		break;
//	}
//
//	// odrysowanie okna
//	DisplayScene();
//}
//
//// obs�uga menu podr�cznego
//
//void Menu(int value)
//{
//	switch (value)
//	{
//		// rysowany obiekt - kula
//	case SPHERE:
//		object = SPHERE;
//		DisplayScene();
//		break;
//
//		// rysowany obiekt - czajnik
//	case TEAPOT:
//		object = TEAPOT;
//		DisplayScene();
//		break;
//
//		// rysowany obiekt - sto�ek
//	case CONE:
//		object = CONE;
//		DisplayScene();
//		break;
//
//		// rysowany obiekt - torus
//	case TORUS:
//		object = TORUS;
//		DisplayScene();
//		break;
//
//		// rysowany obiekt - sze�cian
//	case CUBE:
//		object = CUBE;
//		DisplayScene();
//		break;
//
//		// rysowany obiekt - dwunasto�cian
//	case DODECAHEDRON:
//		object = DODECAHEDRON;
//		DisplayScene();
//		break;
//
//		// rysowany obiekt - o�mio�cian
//	case OCTAHEDRON:
//		object = OCTAHEDRON;
//		DisplayScene();
//		break;
//
//		// rysowany obiekt - czworo�cian
//	case TETRAHEDRON:
//		object = TETRAHEDRON;
//		DisplayScene();
//		break;
//
//		// rysowany obiekt - dwudziesto�cian
//	case ICOSAHEDRON:
//		object = ICOSAHEDRON;
//		DisplayScene();
//		break;
//
//		// materia� - mosi�dz
//	case BRASS:
//		ambient = BrassAmbient;
//		diffuse = BrassDiffuse;
//		specular = BrassSpecular;
//		shininess = BrassShininess;
//		DisplayScene();
//		break;
//
//		// materia� - br�z
//	case BRONZE:
//		ambient = BronzeAmbient;
//		diffuse = BronzeDiffuse;
//		specular = BronzeSpecular;
//		shininess = BronzeShininess;
//		DisplayScene();
//		break;
//
//		// materia� - polerowany br�z
//	case POLISHED_BRONZE:
//		ambient = PolishedBronzeAmbient;
//		diffuse = PolishedBronzeDiffuse;
//		specular = PolishedBronzeSpecular;
//		shininess = PolishedBronzeShininess;
//		DisplayScene();
//		break;
//
//		// materia� - chrom
//	case CHROME:
//		ambient = ChromeAmbient;
//		diffuse = ChromeDiffuse;
//		specular = ChromeSpecular;
//		shininess = ChromeShininess;
//		DisplayScene();
//		break;
//
//		// materia� - mied�
//	case COPPER:
//		ambient = CopperAmbient;
//		diffuse = CopperDiffuse;
//		specular = CopperSpecular;
//		shininess = CopperShininess;
//		DisplayScene();
//		break;
//
//		// materia� - polerowana mied�
//	case POLISHED_COPPER:
//		ambient = PolishedCopperAmbient;
//		diffuse = PolishedCopperDiffuse;
//		specular = PolishedCopperSpecular;
//		shininess = PolishedCopperShininess;
//		DisplayScene();
//		break;
//
//		// materia� - z�oto
//	case GOLD:
//		ambient = GoldAmbient;
//		diffuse = GoldDiffuse;
//		specular = GoldSpecular;
//		shininess = GoldShininess;
//		DisplayScene();
//		break;
//
//		// materia� - polerowane z�oto
//	case POLISHED_GOLD:
//		ambient = PolishedGoldAmbient;
//		diffuse = PolishedGoldDiffuse;
//		specular = PolishedGoldSpecular;
//		shininess = PolishedGoldShininess;
//		DisplayScene();
//		break;
//
//		// materia� - grafit (cyna z o�owiem)
//	case PEWTER:
//		ambient = PewterAmbient;
//		diffuse = PewterDiffuse;
//		specular = PewterSpecular;
//		shininess = PewterShininess;
//		DisplayScene();
//		break;
//
//		// materia� - srebro
//	case SILVER:
//		ambient = SilverAmbient;
//		diffuse = SilverDiffuse;
//		specular = SilverSpecular;
//		shininess = SilverShininess;
//		DisplayScene();
//		break;
//
//		// materia� - polerowane srebro
//	case POLISHED_SILVER:
//		ambient = PolishedSilverAmbient;
//		diffuse = PolishedSilverDiffuse;
//		specular = PolishedSilverSpecular;
//		shininess = PolishedSilverShininess;
//		DisplayScene();
//		break;
//
//		// materia� - szmaragd
//	case EMERALD:
//		ambient = EmeraldAmbient;
//		diffuse = EmeraldDiffuse;
//		specular = EmeraldSpecular;
//		shininess = EmeraldShininess;
//		DisplayScene();
//		break;
//
//		// materia� - jadeit
//	case JADE:
//		ambient = JadeAmbient;
//		diffuse = JadeDiffuse;
//		specular = JadeSpecular;
//		shininess = JadeShininess;
//		DisplayScene();
//		break;
//
//		// materia� - obsydian
//	case OBSIDIAN:
//		ambient = ObsidianAmbient;
//		diffuse = ObsidianDiffuse;
//		specular = ObsidianSpecular;
//		shininess = ObsidianShininess;
//		DisplayScene();
//		break;
//
//		// materia� - per�a
//	case PEARL:
//		ambient = PearlAmbient;
//		diffuse = PearlDiffuse;
//		specular = PearlSpecular;
//		shininess = PearlShininess;
//		DisplayScene();
//		break;
//
//		// metaria� - rubin
//	case RUBY:
//		ambient = RubyAmbient;
//		diffuse = RubyDiffuse;
//		specular = RubySpecular;
//		shininess = RubyShininess;
//		DisplayScene();
//		break;
//
//		// materia� - turkus
//	case TURQUOISE:
//		ambient = TurquoiseAmbient;
//		diffuse = TurquoiseDiffuse;
//		specular = TurquoiseSpecular;
//		shininess = TurquoiseShininess;
//		DisplayScene();
//		break;
//
//		// materia� - czarny plastik
//	case BLACK_PLASTIC:
//		ambient = BlackPlasticAmbient;
//		diffuse = BlackPlasticDiffuse;
//		specular = BlackPlasticSpecular;
//		shininess = BlackPlasticShininess;
//		DisplayScene();
//		break;
//
//		// materia� - czarna guma
//	case BLACK_RUBBER:
//		ambient = BlackRubberAmbient;
//		diffuse = BlackRubberDiffuse;
//		specular = BlackRubberSpecular;
//		shininess = BlackRubberShininess;
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
//// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze�
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
//#ifndef WIN32
//		printf("B��dny format wersji OpenGL\n");
//#else
//
//		printf("Bledny format wersji OpenGL\n");
//#endif
//
//		exit(0);
//	}
//
//	// sprawdzenie czy jest co najmniej wersja 1.4
//	if (major > 1 || minor >= 4)
//	{
//		// pobranie wska�nika wybranej funkcji OpenGL 1.4
//		glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress("glWindowPos2i");
//	}
//	else
//		// sprawdzenie czy jest obs�ugiwane rozszerzenie ARB_window_pos
//		if (glutExtensionSupported("GL_ARB_window_pos"))
//		{
//			// pobranie wska�nika wybranej funkcji rozszerzenia ARB_window_pos
//			glWindowPos2i = (PFNGLWINDOWPOS2IPROC)wglGetProcAddress("glWindowPos2iARB");
//		}
//		else
//		{
//			printf("Brak rozszerzenia ARB_window_pos!\n");
//			exit(0);
//		}
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
//
//#ifdef WIN32
//
//	glutCreateWindow("�wiat�o kierunkowe");
//#else
//
//	glutCreateWindow("Swiatlo kierunkowe");
//#endif
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
//	// utworzenie podmenu - obiekt
//	int MenuObject = glutCreateMenu(Menu);
//	glutAddMenuEntry("Kula", SPHERE);
//	glutAddMenuEntry("Czajnik", TEAPOT);
//
//#ifdef WIN32
//
//	glutAddMenuEntry("Sto�ek", CONE);
//	glutAddMenuEntry("Torus", TORUS);
//	glutAddMenuEntry("Sze�cian", CUBE);
//	glutAddMenuEntry("Dwunasto�cian", DODECAHEDRON);
//	glutAddMenuEntry("O�mio�cian", OCTAHEDRON);
//	glutAddMenuEntry("Czworo�cian", TETRAHEDRON);
//	glutAddMenuEntry("Dwudziesto�cian", ICOSAHEDRON);
//#else
//
//	glutAddMenuEntry("Stozek", CONE);
//	glutAddMenuEntry("Torus", TORUS);
//	glutAddMenuEntry("Szescian", CUBE);
//	glutAddMenuEntry("Dwunastoscian", DODECAHEDRON);
//	glutAddMenuEntry("Osmioscian", OCTAHEDRON);
//	glutAddMenuEntry("Czworoscian", TETRAHEDRON);
//	glutAddMenuEntry("Dwudziestoscian", ICOSAHEDRON);
//#endif
//
//	// utworzenie podmenu - Materia�
//	int MenuMaterial = glutCreateMenu(Menu);
//#ifdef WIN32
//
//	glutAddMenuEntry("Mosi�dz", BRASS);
//	glutAddMenuEntry("Br�z", BRONZE);
//	glutAddMenuEntry("Polerowany br�z", POLISHED_BRONZE);
//	glutAddMenuEntry("Chrom", CHROME);
//	glutAddMenuEntry("Mied�", COPPER);
//	glutAddMenuEntry("Polerowana mied�", POLISHED_COPPER);
//	glutAddMenuEntry("Z�oto", GOLD);
//	glutAddMenuEntry("Polerowane z�oto", POLISHED_GOLD);
//	glutAddMenuEntry("Grafit (cyna z o�owiem)", PEWTER);
//	glutAddMenuEntry("Srebro", SILVER);
//	glutAddMenuEntry("Polerowane srebro", POLISHED_SILVER);
//	glutAddMenuEntry("Szmaragd", EMERALD);
//	glutAddMenuEntry("Jadeit", JADE);
//	glutAddMenuEntry("Obsydian", OBSIDIAN);
//	glutAddMenuEntry("Per�a", PEARL);
//	glutAddMenuEntry("Rubin", RUBY);
//	glutAddMenuEntry("Turkus", TURQUOISE);
//	glutAddMenuEntry("Czarny plastik", BLACK_PLASTIC);
//	glutAddMenuEntry("Czarna guma", BLACK_RUBBER);
//#else
//
//	glutAddMenuEntry("Mosiadz", BRASS);
//	glutAddMenuEntry("Braz", BRONZE);
//	glutAddMenuEntry("Polerowany braz", POLISHED_BRONZE);
//	glutAddMenuEntry("Chrom", CHROME);
//	glutAddMenuEntry("Miedz", COPPER);
//	glutAddMenuEntry("Polerowana miedz", POLISHED_COPPER);
//	glutAddMenuEntry("Zloto", GOLD);
//	glutAddMenuEntry("Polerowane zloto", POLISHED_GOLD);
//	glutAddMenuEntry("Grafit (cyna z o�owiem)", PEWTER);
//	glutAddMenuEntry("Srebro", SILVER);
//	glutAddMenuEntry("Polerowane srebro", POLISHED_SILVER);
//	glutAddMenuEntry("Szmaragd", EMERALD);
//	glutAddMenuEntry("Jadeit", JADE);
//	glutAddMenuEntry("Obsydian", OBSIDIAN);
//	glutAddMenuEntry("Perla", PEARL);
//	glutAddMenuEntry("Rubin", RUBY);
//	glutAddMenuEntry("Turkus", TURQUOISE);
//	glutAddMenuEntry("Czarny plastik", BLACK_PLASTIC);
//	glutAddMenuEntry("Czarna guma", BLACK_RUBBER);
//#endif
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
//	glutAddSubMenu("Obiekt", MenuObject);
//
//#ifdef WIN32
//
//	glutAddSubMenu("Materia�", MenuMaterial);
//#else
//
//	glutAddSubMenu("Material", MenuMaterial);
//#endif
//
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
//	// sprawdzenie i przygotowanie obs�ugi wybranych rozszerze�
//	ExtensionSetup();
//
//	// wprowadzenie programu do obs�ugi p�tli komunikat�w
//	glutMainLoop();
//	return 0;
//}
