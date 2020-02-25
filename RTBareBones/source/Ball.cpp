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

void Ball::verifyHitPlayer()
{
	float* box = player->GetBox();
	float minX = box[0];
	float maxX = box[2];
	float minY = box[1];
	float maxY = box[3];

	CollisionSphereRect(minX, maxX, minY, maxY, true);
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
}


void Ball::Init(Player* _player, CL_Vec2f _initialPos, float _radius, uint32 _color, float _speed)
{
	player = _player;
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
	verifyHitPlayer();
	pos.x += 0.01f * speed * dir.x * deltaTick;
	pos.y += 0.01f * speed * dir.y * deltaTick;
}

void Ball::CollisionSphereRect(float minX, float maxX, float minY, float maxY, bool isPlayer)
{
	if (pos.y - radius < minY) return;	

	//remove the ball from inside the rect
	while ((pos.x <= maxX && pos.x >= minX) && (pos.y <= maxY && pos.y >= minY))
	{
		pos.x -= dir.x;
		pos.y -= dir.y;
	}

	// Find the closest point to the circle within the rectangle
	float closestX = Clamp(pos.x, minX, maxX);
	float closestY = Clamp(pos.y, minY, maxY);


	CL_Vec2f closest(closestX, closestY);
	
	// If the distance is less than the circle's radius, an intersection occurs
	float distance = closest.distance(pos);

	bool result = distance < radius;

	if (result)
	{
		if (closestX == minX)
		{
			//topLeftEdge
			if (closestY == minY)
			{
				dir = CL_Vec2f(-1, -1).normalize();
				closestX -= radius;
				closestY -= radius;
			}
			//botLeftEdge
			else if (closestY == maxY)
			{
				dir = CL_Vec2f(-1, 1).normalize();
				closestX -= radius;
				closestY += radius;
			}
			// left
			else
			{
				dir.mirror(CL_Vec2f(-1,0));
				closestX -= radius;
			}
		}
		else if(closestX == maxX)
		{
			//topRightEdge
			if (closestY == minY)
			{
				dir = CL_Vec2f(1, -1).normalize();
				closestX += radius;
				closestY -= radius;
			}
			//botRightEdge
			else if (closestY == maxY)
			{
				dir = CL_Vec2f(1, 1).normalize();
				closestX += radius;
				closestY += radius;
			}
			//right
			else
			{
				dir.mirror(CL_Vec2f(1, 0));
				closestX += radius;
			}
		}
		else
		{			
			//bot
			if (closestY == maxY)
			{
				dir.mirror(CL_Vec2f(0, 1));
				closestY += radius;
			}
			//top
			else
			{
				dir.mirror(CL_Vec2f(0, -1));
				if (isPlayer)
				{
					//TODO: move the ball in the angle
				}
				closestY -= radius;
			}
		}

		pos = CL_Vec2f(closestX, closestY);
	}
}

float Ball::Clamp(float v, float lo, float hi)
{
	return (v < lo) ? lo : (hi < v) ? hi : v;
}
