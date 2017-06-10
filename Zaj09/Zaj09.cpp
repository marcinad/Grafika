#include "stdafx.h"

/*
* (c) Copyright 2016, Vasyl Martsenyuk
* Email: marceniuk@yahoo.com
*/

#include <windows.h> // plik nag��wkowy dla Windows
#include <math.h> // plik nag��wkowy dla biblioteki matematycznej
#include <stdio.h> // plik nag��wkowy dla we/wy standardowego
#include <stdlib.h> // plik nag��wkowy dla bibioteki standardowej
#include <gl\gl.h> // plik nag��wkowy dla biblioteki OpenGL32
#include <gl\glu.h> // plik nag��wkowy dla biblioteki GLu32
#include <GL\glut.h> // plik nag��wkowy dla biblioteki Glut
#include "../Library/glext.h"
#include "../Zaj09/targa.h"
#include "stdio.h"

// sta�e do obs�ugi menu podr�cznego

enum
{
	VENUS_TEX, // Wenus
	EARTH_TEX, // Ziemia
	MARS_TEX, // Mars
	FULL_WINDOW, // aspekt obrazu - ca�e okno
	ASPECT_1_1, // aspekt obrazu 1:1
	EXIT // wyj�cie
};

// aspekt obrazu

int aspect = ASPECT_1_1;

// rozmiary bry�y obcinania

const GLdouble left = -2.0;
const GLdouble right = 2.0;
const GLdouble bottom = -2.0;
const GLdouble top = 2.0;
const GLdouble near_ = -4.0;
const GLdouble far_ = 4.0;

// k�ty obrotu

GLfloat rotatex = 0.0;
GLfloat rotatez = 0.0;

// wska�nik naci�ni�cia lewego przycisku myszki

int button_state = GLUT_UP;

// po�o�enie kursora myszki

int button_x, button_y;

// wsp�czynnik skalowania

GLfloat scale = 3.5;

typedef struct point_3d { // struktura dla punktu 3D

	double x, y, z;

} POINT_3D;



typedef struct bpatch { // struktura dla wielomiana fragmentu Beziera 3 stopnia

	POINT_3D anchors[4][4]; // siatka 4x4 punkt�w kontrolnych (anchor)

	GLuint dlBPatch; // lista dla fragmentu Beziera

	GLuint texture; // tekstura dla fragmentu

} BEZIER_PATCH;



HDC hDC = NULL; // kontekst urz�dzenia

HGLRC hRC = NULL; // kontekst renderingu

HWND hWnd = NULL; // deskryptor okna

HINSTANCE hInstance; // egzemplarz programu



bool keys[256]; // tablica jednowymiarowa dla klawiatury

bool active = TRUE; // flag of application activity

bool fullscreen = TRUE; // flag of full-screen mode



DEVMODE DMsaved; // zachowa� ustawienia przesz�ego trybu



GLfloat rotz = 0.0f; // obroty wsp�rz�dnej Z

BEZIER_PATCH mybezier; // fragment Beziera dla wykorzystania

bool showCPoints = TRUE; // switcher of anchor points of net

int divs = 7; // number of interpolation (distribution of polygon)



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // deklaracja dla WndProc

													  //functions for vector operations. It can be used any C++ class for 3D point

													  // addition of 2 points

POINT_3D pointAdd(POINT_3D p, POINT_3D q) {

	p.x += q.x; p.y += q.y; p.z += q.z;

	return p;

}



// multiplication of point by constant

POINT_3D pointTimes(double c, POINT_3D p) {

	p.x *= c; p.y *= c; p.z *= c;

	return p;

}



// making new point

POINT_3D makePoint(double a, double b, double c) {

	POINT_3D p;

	p.x = a; p.y = b; p.z = c;

	return p;

}

//function for calculation of 3rd order polynomial (each counterpart in Bezie curve equation is one of so called
// Bernstane polynomials); it necessary to transfer variable u and array containing 4 points p
// and to calculate point on curve. Changing u with the same increments between 0 and 1 we get
// good curve approximation



// calculate polynomial of 3rd order based on array of 4 points

// and variable u changed from 0 to 1

POINT_3D Bernstein(float u, POINT_3D *p) {

	POINT_3D a, b, c, d, r;



	a = pointTimes(pow(u, 3), p[0]);

	b = pointTimes(3 * pow(u, 2)*(1 - u), p[1]);

	c = pointTimes(3 * u*pow((1 - u), 2), p[2]);

	d = pointTimes(pow((1 - u), 3), p[3]);



	r = pointAdd(pointAdd(a, b), pointAdd(c, d));



	return r;

}

//this function generates all slices of triangles and stores them in display list.
// we do it in order not to recalculate fragment during each frame.
// Meanwhile we can use morphing of anchor points. We will get intereting effect of smoothed low-cost morphing.
// (we only do morphing of 16 points but we should recalculate them). Array "last" is used to store previous line
// of points (since for triangular slices both raws are needed).
// Also coordinates of texture are calculated with help of values of u and v in form of procents (flat covering).

// We don't do calculation of normals for lighting.
// For this purpose we need 2 parameters.
// The first paramater is the center of each triangle
// and then to use bitwise calculus and calculation of tan of both axes x and y,
// then to calculate vector product in order to get perpendicular for both axes and then
// to normalize vector and to use it as normal.



GLuint genBezier(BEZIER_PATCH patch, int divs) {

	int u = 0, v;

	float py, px, pyold;

	GLuint drawlist = glGenLists(1);

	POINT_3D temp[4];

	POINT_3D *last = (POINT_3D*)malloc(sizeof(POINT_3D)*(divs + 1));



	if (patch.dlBPatch != NULL)

		glDeleteLists(patch.dlBPatch, 1);



	temp[0] = patch.anchors[0][3];

	temp[1] = patch.anchors[1][3];

	temp[2] = patch.anchors[2][3];

	temp[3] = patch.anchors[3][3];



	for (v = 0; v <= divs; v++) {

		px = ((float)v) / ((float)divs);



		last[v] = Bernstein(px, temp);

	}



	glNewList(drawlist, GL_COMPILE);

	glBindTexture(GL_TEXTURE_2D, patch.texture);



	for (u = 1; u <= divs; u++) {

		py = ((float)u) / ((float)divs);

		pyold = ((float)u - 1.0f) / ((float)divs);



		temp[0] = Bernstein(py, patch.anchors[0]);

		temp[1] = Bernstein(py, patch.anchors[1]);

		temp[2] = Bernstein(py, patch.anchors[2]);

		temp[3] = Bernstein(py, patch.anchors[3]);



		glBegin(GL_TRIANGLE_STRIP);



		for (v = 0; v <= divs; v++) {

			px = ((float)v) / ((float)divs);



			glTexCoord2f(pyold, px);

			glVertex3d(last[v].x, last[v].y, last[v].z);



			last[v] = Bernstein(px, temp);

			glTexCoord2f(py, px);

			glVertex3d(last[v].x, last[v].y, last[v].z);

		}



		glEnd();

	}



	glEndList();



	free(last);

	return drawlist; 

}





void initBezier(void) {

	mybezier.anchors[0][0] = makePoint(-0.75, -0.75, -0.50);

	mybezier.anchors[0][1] = makePoint(-0.25, -0.75, 0.00);

	mybezier.anchors[0][2] = makePoint(0.25, -0.75, 0.00);

	mybezier.anchors[0][3] = makePoint(0.75, -0.75, -0.50);

	mybezier.anchors[1][0] = makePoint(-0.75, -0.25, -0.75);

	mybezier.anchors[1][1] = makePoint(-0.25, -0.25, 0.50);

	mybezier.anchors[1][2] = makePoint(0.25, -0.25, 0.50);

	mybezier.anchors[1][3] = makePoint(0.75, -0.25, -0.75);

	mybezier.anchors[2][0] = makePoint(-0.75, 0.25, 0.00);

	mybezier.anchors[2][1] = makePoint(-0.25, 0.25, -0.50);

	mybezier.anchors[2][2] = makePoint(0.25, 0.25, -0.50);

	mybezier.anchors[2][3] = makePoint(0.75, 0.25, 0.00);

	mybezier.anchors[3][0] = makePoint(-0.75, 0.75, -0.50);

	mybezier.anchors[3][1] = makePoint(-0.25, 0.75, -1.00);

	mybezier.anchors[3][2] = makePoint(0.25, 0.75, -1.00);

	mybezier.anchors[3][3] = makePoint(0.75, 0.75, -0.50);

	mybezier.dlBPatch = NULL;

}





int InitGL(GLvoid)

{

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glClearColor(1.00f, 1.00f, 1.00f, 0.5f); // ??? bia�y

	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);	

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);



	initBezier();

	// wczytanie tekstury Venus utworzonej ze zdj�� sondy Magellan
	// plik: http://maps.jpl.nasa.gov/pix/ven0aaa2.tif
	GLsizei width_texture, height_texture; // zmienne u�yte przy obs�udze plik�w TARGA
	GLenum format, type;
	GLvoid *Ptr_mybezier_texture;
	GLboolean error = load_targa("water_plain_sea_4.tga", width_texture, height_texture, format, type, Ptr_mybezier_texture);


	// b��d odczytu pliku
	if (error == GL_FALSE)
	{
		printf("Niepoprawny odczyt pliku mar0kuu2.tga");
		exit(0);
	}


	// dowi�zanie stanu tekstury
	glBindTexture(GL_TEXTURE_2D, (GLuint)Ptr_mybezier_texture);

	// utworzenie tekstury wraz z mipmapami
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width_texture, height_texture, format, type, Ptr_mybezier_texture);

	///////////////////
	mybezier.texture = (GLuint)Ptr_mybezier_texture;
	///////////////////
	mybezier.dlBPatch = genBezier(mybezier, divs);

	// porz�dki
	delete[](GLvoid*)Ptr_mybezier_texture;

	return TRUE;

}




void DrawGLScene(GLvoid) {

	int i, j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	////////////////////
	glLoadIdentity();


	// obroty obiektu
	glRotatef(-75.0f, 1.0f, 0.0f, 0.0f);


	// przesuni�cie uk�adu wsp�rz�dnych obiekt�w do �rodka bry�y odcinania
	glTranslatef(0.0, 0.0, -(near_ + far_) / 2);

	// obroty obiektu
	glRotatef(rotatex, 1.0, 0.0, 0.0);
	glRotatef(rotatez, 0.0, 0.0, 1.0);

	// skalowanie obiektu - klawisze "+" i "-"
	glScalef(scale, scale, scale);


	glCallList(mybezier.dlBPatch);




	BOOL showCPoint = TRUE;
	if (showCPoints)
	{

		glDisable(GL_TEXTURE_2D);

		glColor3f(0.0f, 1.0f, 0.0f);

		// rozmiar punkt�w
		glPointSize(6.0);

		for (i = 0; i<4; i++) {

			glBegin(GL_LINE_STRIP);


			for (j = 0; j<4; j++)

				glVertex3d(mybezier.anchors[i][j].x, mybezier.anchors[i][j].y, mybezier.anchors[i][j].z);

			glEnd();

		}

		for (i = 0; i<4; i++) {

			glBegin(GL_LINE_STRIP);


			for (j = 0; j<4; j++)

				glVertex3d(mybezier.anchors[j][i].x, mybezier.anchors[j][i].y, mybezier.anchors[j][i].z);

			glEnd();

		}

		glColor3f(1.0f, 1.0f, 1.0f);

		glEnable(GL_TEXTURE_2D);

	}

	// wy�wietlenie sceny
	glutPostRedisplay();

	//return TRUE;
	glFlush();

	glutSwapBuffers();

}

void resize(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5, 5, -5, 5, 2, 12);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	DrawGLScene();
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
	DrawGLScene();
}

int main(int argc, char *argv[])
{
	// inicjalizacja biblioteki GLUT
	glutInit(&argc, argv);

	// inicjalizacja bufora ramki
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(50, 10);

	// rozmiary g��wnego okna programu
	glutInitWindowSize(500, 500);

	// utworzenie g��wnego okna programu
	glutCreateWindow("Krzywa Beziera");

	// do��czenie funkcji generuj�cej scen� 3D
	glutDisplayFunc(DrawGLScene);

	// do��czenie funkcji wywo�ywanej przy zmianie rozmiaru okna
	glutReshapeFunc(resize);
	//glutReshapeFunc(Reshape);

	// do��czenie funkcji obs�ugi klawiatury
	glutKeyboardFunc(Keyboard);

	// obs�uga przycisk�w myszki
	glutMouseFunc(MouseButton);

	// obs�uga ruchu kursora myszki
	glutMotionFunc(MouseMotion);

	InitGL();

	// wprowadzenie programu do obs�ugi p�tli komunikat�w
	glutMainLoop();

	// porz�dki
	delete[](GLvoid*)mybezier.texture;

	return 0;
}