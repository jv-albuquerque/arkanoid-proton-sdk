#include "PlatformPrecomp.h"
#include "Ball.h"

void Ball::verifyOutOfScreen()
{
}

void Ball::Update(float deltaTick)
{
	Move();
}

void Ball::Init(CL_Vec2f _initialPos, float _radius, uint32 _color, float _speed)
{
	pos = _initialPos;
	radius = _radius;
	color = _color;
	speed = _speed;
}

void Ball::Draw()
{
	DrawCircle(pos, radius, color);
}

void Ball::Move()
{
	verifyOutOfScreen();
}
