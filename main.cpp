#include<GL/glut.h>
#include<Windows.h>
//#include"Camera.h"
#include<iostream>
using namespace std;

static GLfloat MatSpec[] = { 1.0,1.0,1.0,1.0 };
static GLfloat MatShininess[] = { 100.0 };
static GLfloat LightPos[] = { -2.0,1.0,3.0,0.0 };

float angle = 0, angleY = 0, theta = 0;
int rollx = 1, rolly = 1, rollz = 1;

CamView Camera;

void DrawGrid(GLfloat size, GLint LinesX, GLint LinesZ)
{
	glBegin(GL_LINES);
	for (int xc = 0; xc < LinesX; xc++)
	{
		glVertex3f(-size / 2 + xc / (GLfloat)(LinesX - 1) * size, 0, size / 2);
		glVertex3f(-size / 2 + xc / (GLfloat)(LinesX - 1) * size, 0, size / -2);
	}
	for (int zc = 0; zc < LinesX; zc++)
	{
		glVertex3f(size / 2, 0, -size / 2 + zc / (GLfloat)(LinesZ - 1) * size);
		glVertex3f(size / -2, 0, -size / 2 + zc / (GLfloat)(LinesZ - 1) * size);
	}
	glEnd();
}

void Reshape(int x, int y)
{
	if (y == 0 || x == 0)
		return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (GLdouble)x / (GLdouble)y, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
	glPointSize(GLfloat(x) / 200.0);
}

void Display(void)
{
	glClearColor(0.1, 0.1, 0.1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Camera.Render();
	
	gluLookAt(3 * cos(angle), 3*sin(angleY), 3 * sin(angle), 0, 0, 0, 0, 1,0);

	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);

	GLfloat size = 10;
	GLint LinesX = 30;
	GLint LinesZ = 30;

	GLfloat halfsize = size / 2;

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0, -0.5, 0);
	DrawGrid(size, LinesX, LinesZ);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void KeyIn(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		angle += 0.1;
		Display();
		break;

	case GLUT_KEY_LEFT:
		angle -= 0.1;
		Display();
		break;

	case GLUT_KEY_UP:
		angleY += 0.1;
		Display();
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Camera Movement");
	Camera.Move(F3dVector(0, 0, 3));
	Camera.MoveForwards(1);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(KeyIn);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutMainLoop();
	return 0;
}
