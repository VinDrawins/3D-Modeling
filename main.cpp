#include<GL/glut.h>
#include<Windows.h>
#include"Camera.h"

static GLfloat MatSpec[] = { 1.0,1.0,1.0,1.0 };
static GLfloat MatShininess[] = { 100.0 };
static GLfloat LightPos[] = { -2.0,1.0,3.0,0.0 };

CamView Camera;

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Camera.Render();
	glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
	
	glPushMatrix();
	glTranslatef(10, 0, 0);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glutSolidSphere(1.0, 20, 20);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:PostQuitMessage(0);
		break;
	case 'a':
		Camera.RotateY(5);
		Display();
		break;
	case 'd':
		Camera.RotateY(-5);
		Display();
		break;
	case 'w':
		Camera.MoveForwards(-0.1);
		Display();
		break;
	case 's':
		Camera.MoveForwards(0.1);
		Display();
		break;
	case 'x':
		Camera.RotateX(5);
		Display();
		break;
	case 'y':
		Camera.RotateX(-5);
		Display();
		break;
	case 'c':
		Camera.StrafeRight(-0.1);
		Display();
		break;
	case 'v':
		Camera.StrafeRight(0.1);
		Display();
		break;
	case 'f':
		Camera.Move(F3dVector(0, -0.3, 0));
		Display();
		break;
	case 'r':
		Camera.Move(F3dVector(0, 0.3, 0));
		Display();
		break;
	default:
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
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyInput);

	glShadeModel(GL_FLAT);	//GL_FLAT would look much worse
	glEnable(GL_DEPTH_TEST);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glutMainLoop();
	return 0;
}