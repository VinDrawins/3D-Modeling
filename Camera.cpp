#include "Camera.h"
#include<math.h>
#include<iostream>
#include<Windows.h>

Cam3dVector F3dVector(GLfloat x, GLfloat y, GLfloat z)
{
	Cam3dVector temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;
	return temp;
}

Cam3dVector AddF3dVectors(Cam3dVector* u, Cam3dVector* v)
{
	Cam3dVector result;
	result.x = u->x + v->x;
	result.y = u->y + v->y;
	result.z = u->z + v->z;
	return result;
}

void AddF3dVectorToVector(Cam3dVector* Dist, Cam3dVector* v2)
{
	Dist->x += v2->x;
	Dist->y += v2->y;
	Dist->z += v2->z;
}

CamView::CamView()
{
	Position = F3dVector(0, 0, 0);
	ViewDirection = F3dVector(0, 0, -1);
	ViewDirection_Changed = false;
	RotatedX = RotatedY = RotatedZ = 0;
}

void CamView::GetViewDirection(void)
{
	Cam3dVector step1, step2;

	//Rotate around Y-axis
	step1.x = cos((RotatedX + 90) * PiDiv180);
	step1.z = sin((RotatedY + 90) * PiDiv180);

	//Rotate around X-axis
	double cosX = cos(RotatedX * PiDiv180);
	step2.x = step1.x * cosX;
	step2.z = step1.z * cosX;
	step2.y = sin(RotatedX * PiDiv180);

	ViewDirection = step2;
}

void CamView::Move(Cam3dVector Direction)
{
	AddF3dVectorToVector(&Position, &Direction);
}

void CamView::RotateX(GLfloat Angle)
{
	RotatedX += Angle;
	ViewDirection_Changed = true;
}

void CamView::RotateY(GLfloat Angle)
{
	RotatedY += Angle;
	ViewDirection_Changed = true;
}

void CamView::Render(void)
{
	glRotatef(-RotatedX, 1, 0, 0);
	glRotatef(-RotatedY, 0, 1, 0);
	glRotatef(-RotatedZ, 0, 0, 1);
	glTranslatef(-Position.x, -Position.y, -Position.z);
}

void CamView::MoveForwards(GLfloat Distance)
{
	if (ViewDirection_Changed)
		GetViewDirection();
	Cam3dVector MoveVector;
	MoveVector.x = ViewDirection.x * -Distance;
	MoveVector.y = ViewDirection.y * -Distance;
	MoveVector.z = ViewDirection.z * -Distance;
	AddF3dVectorToVector(&Position, &MoveVector);
}

void CamView::StrafeRight(GLfloat Distance)
{
	if (ViewDirection_Changed)
		GetViewDirection();
	Cam3dVector MoveVector;
	MoveVector.z = -ViewDirection.x * -Distance;
	MoveVector.y = 0;
	MoveVector.x = ViewDirection.z * -Distance;
	AddF3dVectorToVector(&Position, &MoveVector);
}