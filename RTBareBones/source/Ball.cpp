#include "PlatformPrecomp.h"
#include "Ball.h"

void Ball::verifyOutOfScreen()
{
}

void Ball::Update(float deltaTick)
{
	Move(deltaTick);
}

void Ball::Init(CL_Vec2f _initialPos, float _radius, uint32 _color, float _speed)
{
	pos = _initialPos;
	radius = _radius;
	color = _color;
	speed = _speed;

	CL_Vec2f newDir(RandomRangeFloat(0, 1), RandomRangeFloat(0, 1));
	newDir.normalize();

	dir = newDir;
}

void Ball::Draw()
{
	DrawCircle(pos, radius, color);
}

void Ball::Move(float deltaTick)
{
	verifyOutOfScreen();
	pos.x += 0.01f * speed * dir.x * deltaTick;
	pos.y += 0.01f * speed * dir.y * deltaTick;
}
