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
GLfloat updateX = 0, updateY = 0;
GLfloat xtrans, ytrans;
float fov_y = 40.0f, cRadius = 5; //fov = Field of View.
bool panning;

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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		angleX += changeAngleX;
		angleY += changeAngleY;
		xOrigin = -1;
		yOrigin = -1;
		cout << endl;
	}
		
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xOrigin = MouseX;
		yOrigin = MouseY;
		panning = false;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mod == 4)
	{
		panning = true;
	}
}

void MouseMove(int MouseX, int MouseY)
{
	changeAngleX = (MouseX - xOrigin);
	changeAngleY = (MouseY - yOrigin);

	cout << "Updated X: " << updateX << " ," << "Updated Y: " << updateY << endl;

	if (panning == true)
	{
		float ndc_x = changeAngleX * 2.0f / 500;
		float ndc_y = -changeAngleY * 2.0f / 500;
		float aspect = 500 / 500;
		float fov_rad = fov_y * M_PI / 180.0;
		float tanfov = tan(fov_rad / 2.0);

		xtrans = ndc_x * cRadius * tanfov * aspect;
		ytrans = ndc_y * cRadius * tanfov;
	}
	else
	{
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
