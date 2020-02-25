#include "PlatformPrecomp.h"
#include "Ball.h"

void Ball::verifyOutOfScreen()
{
	float rightLimit = GetScreenSizeX() - radius;
	float bottomLimit = GetScreenSizeY() - radius;

	//left limit
	if (pos.x <= 0 + radius)
	{
		pos.x = 0 + radius;
		dir.mirror(CL_Vec2f(1,0));
	}
	//right limit
	else if (pos.x >= rightLimit)
	{
		pos.x = rightLimit;
		dir.mirror(CL_Vec2f(-1, 0));
	}
	//top limit
	else if (pos.y <= 0 + radius)
	{
		pos.y = 0 + radius;
		dir.mirror(CL_Vec2f(0, 1));
	}
	//bottom limit
	else if (pos.y >= bottomLimit)
	{
		pos.y = bottomLimit;
		dir.mirror(CL_Vec2f(0, -1));
	}
}

void Ball::Update(float deltaTick)
{
	Move(deltaTick);
}

void Ball::reset()
{
	pos = CL_Vec2f(float(GetScreenSizeX()) / 2, float(GetScreenSizeY()) / 2);

	CL_Vec2f newDir(RandomRangeFloat(-1, 1), RandomRangeFloat(-1, 1));
	newDir.normalize();

	dir = newDir;

	LogMsg("%f : %f", dir.x, dir.y);
}

void Ball::Init(CL_Vec2f _initialPos, float _radius, uint32 _color, float _speed)
{
	pos = _initialPos;
	radius = _radius;
	color = _color;
	speed = _speed;

	CL_Vec2f newDir(RandomRangeFloat(-1, 1), RandomRangeFloat(0, 1));
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
