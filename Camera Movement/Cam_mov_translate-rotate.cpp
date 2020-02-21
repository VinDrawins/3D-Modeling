#define _USE_MATH_DEFINES
#include<GL/glut.h>
#include<Windows.h>
#include<iostream>
#include<math.h>
using namespace std;

static GLfloat MatSpec[] = { 1.0,1.0,1.0,1.0 };
static GLfloat MatShininess[] = { 100.0 };
static GLfloat LightPos[] = { -2.0,1.0,3.0,0.0 };

GLfloat angleX = 0.1, angleY = 0.1, changeAngleX = 0, changeAngleY = 0;
GLint xOrigin = -1, yOrigin = -1;
GLint xOrigin_pan = -1, yOrigin_pan = -1;
GLfloat changeAngleX_pan = 0, changeAngleY_pan = 0;
GLfloat updateX = 0, updateY = 0;
float xtrans, ytrans;
float fov_y = 40.0f, cRadius = 5;	//fov = Field of View.
bool panning;
float ndc_x, ndc_y, ndc_x1, ndc_y1;

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
	gluPerspective(fov_y, (GLdouble)x / (GLdouble)y, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
	glPointSize(GLfloat(x) / 200.0);
}

void Display(void)
{
	glClearColor(0.1, 0.1, 0.1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	

	glTranslatef(xtrans, ytrans, -5);
	glRotatef(updateY, 1, 0, 0);
	glRotatef(updateX, 0, 1, 0);
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
	int mod = glutGetModifiers();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && mod == 4)		//Input: hold(ALT) + release(LEFT_MOUSE_BUTTON )
	{
		angleX += changeAngleX;
		angleY += changeAngleY;
		xOrigin = -1;
		yOrigin = -1;
	}
		
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mod == 4)		//Input: press (ALT + LEFT_MOUSE_BUTTON + Mouse-Movement)
	{
		xOrigin = MouseX;
		yOrigin = MouseY;
		panning = false;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && mod == 1)		//Input: hold(SHIFT) + release(LEFT_MOUSE_BUTTON )
	{
		ndc_x1 += ndc_x;
		ndc_y1 += ndc_y;
		xOrigin_pan = -1;
		yOrigin_pan = -1;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mod == 1)		//Input: press (SHIFT + LEFT_MOUSE_BUTTON + Mouse-Movement)  
	{
		xOrigin_pan = MouseX;
		yOrigin_pan = MouseY;
		panning = true;
	}
}

void MouseMove(int MouseX, int MouseY)
{
	if (panning == true)
	{		
		changeAngleX_pan = (MouseX - xOrigin_pan);
		changeAngleY_pan = (MouseY - yOrigin_pan);
		ndc_x = changeAngleX_pan * 2.0f / 500;		//ndc_x = No direction change in x-field
		ndc_y = -changeAngleY_pan * 2.0f / 500;		//ndc_y = No direction change in y-field

		xtrans = ndc_x1 + ndc_x;
		ytrans = ndc_y1 + ndc_y;
	}
	else
	{
		changeAngleX = (MouseX - xOrigin);
		changeAngleY = (MouseY - yOrigin);
		updateX = angleX + changeAngleX;
		updateY = angleY + changeAngleY;
	}
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
