#include <iostream>
#include <windows.h>
#include <glut.h>   
#include <cmath>

#define M_PI 3.1415926535897932384626433832795

GLint Width = 800, Height = 600;
float ZOOMX = 6.0;
float ZOOMY = 6.0;
float dx = M_PI, dy = M_PI;
//int mouseX=0, mouseY=0;
//int isPress = 0;

//void MouseFunc(int button, int state, int x, int y)
//{
//	mouseX=x;
//	mouseY=y;
//}

//void mouseDraw()
//{
//	glColor3ub(255, 0, 0);
//	glPointSize(5);
//	glBegin(GL_POINTS);
//	if (isPress == 1)
//	{
//		std::cout << "ok\n";
//	}
//	if (isPress== GLUT_LEFT_BUTTON)
//	{
//		glVertex2f(mouseX / ZOOMX, mouseY / ZOOMY);
//		std::cout << "click\n";
//	}
//	glEnd();
//	glutSwapBuffers();
//}
double func(float x)
{
	float tmpSin = sin(x / 4);
	return tmpSin*tmpSin + sqrt(x);
}

void DrawGrid()
{
	glBegin(GL_LINES);
	glColor3ub(224, 225, 225);
	for (float i = 0; i < Width; i += dx*ZOOMX)
	{
		glVertex2f(i / ZOOMX, 0 );
		glVertex2f(i / ZOOMX, Height / ZOOMY);
	}
	glVertex2f(Width / (2 * ZOOMX), 0);
	glVertex2f(Width / (2 * ZOOMX), Height / ZOOMY);
	for (float i = 0; i < Height; i += dy*ZOOMY)
	{
		glVertex2f(0 , i / ZOOMY);
		glVertex2f(Width / ZOOMX, i / ZOOMY);
	}
	glEnd();
}

void DrawOxis()
{
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	//X
	glVertex2f(0.0, Height / (ZOOMX*2));
	glVertex2f(Width/ZOOMY, Height / (ZOOMX * 2));	
	for (float i = Width/2; i < Width; i += dx*ZOOMX)
	{
		glVertex2f(i / ZOOMX, (Height / 2 + 2.5)/ZOOMY);
		glVertex2f(i / ZOOMX, (Height / 2 - 2.5)/ZOOMY);
	}
	//Y
	glVertex2f(Width / (2*ZOOMX), 0);
	glVertex2f(Width / (2*ZOOMX), Height/ZOOMY);
	for (float i = 0; i < Height; i += dy*ZOOMY)
	{
		glVertex2f((Width / 2 + 2.5)/ZOOMX, i/ZOOMY);
		glVertex2f((Width / 2 - 2.5)/ZOOMX, i / ZOOMY);
	}
	glEnd();
}

void DrawMyFunc()
{
	glBegin(GL_POINTS);
	glColor3ub(255, 0, 0);
	for (float x = 3 * M_PI / 2; x < 17 * M_PI; x = x + 0.00001)
	{
		glVertex2f(x, func(x));
	}
	glEnd();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glPushMatrix();	
	glScalef(ZOOMX, ZOOMY, 0.0);	
	DrawGrid();
	DrawOxis();
	glTranslated(Width / 2/ZOOMX, Height / 2/ZOOMY, 0);
	glColor3ub(255, 0.0, 0.0);	
	DrawMyFunc();
	//mouseDraw();	
	glPopMatrix();
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
	{
		//exit(0);
		dx += 1.0; dy += 1.0;
		std::cout << "zoom dx:" << dx << ", dy:" << dy << '\n';
		Display();
	}
	if (key == 'x')
	{
		ZOOMX += 0.5;
		std::cout << "zoom X:" << ZOOMX << "\n";
		Display();
	}
	if (key == 'y')
	{
		ZOOMY += 0.5;
		std::cout << "zoom Y:" << ZOOMY << "\n";
		Display();
	}
}

void main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("lab3-graphic");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	//glutMouseFunc(MouseFunc);
	glutPositionWindow(500, 100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutDisplayFunc(Display);	
	glutMainLoop();
}