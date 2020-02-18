#include<GL/glut.h>
#include<Windows.h>
#include<iostream>
using namespace std;

static GLfloat MatSpec[] = { 1.0,1.0,1.0,1.0 };
static GLfloat MatShininess[] = { 100.0 };
static GLfloat LightPos[] = { -2.0,1.0,3.0,0.0 };

GLdouble eyeX=1, eyeY=1, eyeZ=1;
GLfloat angle = 0.1, angleY = 0.1, changeAngleX = 0, changeAngleY = 0;
GLint xOrigin = -1, yOrigin = -1;

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
	

	glTranslatef(0, 0, -5);
	glRotatef(changeAngleY, 1, 0, 0);
	glRotatef(changeAngleX, 0, 1, 0);
	glTranslatef(-1, -1, 0);

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
	glTranslatef(1, 1, 0);
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void MouseInput(int button, int state, int MouseX, int MouseY)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			angle += changeAngleX;
			angleY += changeAngleY;
			xOrigin = -1;
			yOrigin = -1;
		}
		else
		{
			xOrigin = MouseX;
			yOrigin = MouseY;
		}
	}
}

void MouseMove(int MouseX, int MouseY)
{
		changeAngleX = (MouseX - xOrigin);
		changeAngleY = (MouseY - yOrigin);
		Display();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Camera Movement");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(MouseInput);
	glutMotionFunc(MouseMove);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutMainLoop();
	return 0;
}
