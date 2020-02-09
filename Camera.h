#include<GL/glut.h>
#define Pi 3.14
#define PiDiv180 3.14/180.0

struct Cam3dVector
{
	GLfloat x, y, z;
};

struct Cam2dVector
{
	GLfloat x, y;
};

class CamView
{
private:
	Cam3dVector Position;
	Cam3dVector ViewDirection;

	bool ViewDirection_Changed;
	GLfloat RotatedX, RotatedY, RotatedZ;
	void GetViewDirection(void);
public:
	CamView();
	void Render(void);

	void Move(Cam3dVector Direction);
	void RotateX(GLfloat Angle);
	void RotateY(GLfloat Angle);
	void RotateZ(GLfloat Angle);
	void RotateXYZ(Cam3dVector Angles);
	void MoveForwards(GLfloat Distance);
	void StrafeRight(GLfloat Distance);
};

Cam3dVector F3dVector(GLfloat x, GLfloat y, GLfloat z);
Cam3dVector AddF3dVectors(Cam3dVector* u, Cam3dVector* v);
void AddF3dVectorToVector(Cam3dVector* Dist, Cam3dVector* v2);