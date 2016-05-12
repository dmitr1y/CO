#include <iostream>
#include <windows.h>
#include <glut.h>   
#include <cmath>

#define M_PI 3.1415926535897932384626433832795
#define MARGIN_BOTTOM 50
#define MARGIN_LEFT 50
#define SCALE 10
#define ZOOM 6

double func(float x)
{
	float tmpSin = sin(x / 4);
	return SCALE*tmpSin*tmpSin+sqrt(x);
}

GLint Width = 800, Height = 600;

void DrawOxis()
{
	
	
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2f( 0.0, Height / 2);
	glVertex2f(Width, Height/2);
	for (float i = 0; i < Width; i+= M_PI)
	{
		glVertex2f(i, Height / 2 +5);
		glVertex2f(i, Height / 2-5);
	}
	glVertex2f(Width / 2, 0);
	glVertex2f(Width/2, Height);
	for (float i = 0; i < Height; i += M_PI)
	{
		glVertex2f(Width / 2+5, i);
		glVertex2f(Width / 2-5, i);
	}
	glEnd();
//	glFinish();
}

void Display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	DrawOxis();
	glScalef(ZOOM, ZOOM, ZOOM);  
	glColor3ub(255, 0.0, 0.0);

	glBegin(GL_POINTS);
	for (float x = 3*M_PI/2; x < 17*M_PI; x=x+0.00001)
	{
		glVertex2f(MARGIN_LEFT+ x,MARGIN_BOTTOM+ func(x));
	}
	glEnd();

	glFlush();
}

void Reshape(GLint w, GLint h)
{
	Width = w;
	Height = h;

	glViewport(0, 0, w, h);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
#define ESCAPE '\033'

	if (key == ESCAPE)
		exit(0);
}

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("lab3-graphic");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();
}