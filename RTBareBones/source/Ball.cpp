#include "PlatformPrecomp.h"
#include "Ball.h"

bool Ball::verifyOutOfScreen()
{
	float rightLimit = GetScreenSizeX() - radius;
	float bottomLimit = GetScreenSizeY() - radius;

	//left limit
	if (pos.x <= 0 + radius)
	{
		pos.x = 0 + radius;
		dir.mirror(CL_Vec2f(1, 0));
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
		reset();
	}
	else
		return false;

	return true;
}

bool Ball::verifyHitPlayer()
{
	float* box = player->GetBox();

	float minX = box[0];
	float maxX = box[2];
	float minY = box[1];
	float maxY = box[3];

	return CollisionSphereRect(minX, maxX, minY, maxY, true);
}

bool Ball::verifyHitBlocks()
{
	list<Block>::iterator it;

	for (it = blocks->begin(); it != blocks->end(); it++)
	{
		float* box = it->GetBox();

		float minX = box[0];
		float maxX = box[2];
		float minY = box[1];
		float maxY = box[3];

		if (CollisionSphereRect(minX, maxX, minY, maxY))
		{
			//TODO: create a callback to increase the points
			if(it->Hit(1))
				blocks->erase(it);
			return true;
		}
	}

	return false;
}

void Ball::Update(float deltaTick)
{
	Move(deltaTick);
}

void Ball::reset()
{
	notLaunched = true;
	pos = player->initialBallPos() - CL_Vec2f(0, radius);

	dir = CL_Vec2f(0, 0);
}

void Ball::Launch()
{
	if(notLaunched)
	{
		notLaunched = false;
		dir = CL_Vec2f(player->GetMoveScale(), -1);
		dir.normalize();
	}
}


void Ball::Init(Player* _player, list<Block>* _blocks, float _radius, uint32 _color, float _speed)
{
	player = _player;
	blocks = _blocks;
	radius = _radius;
	color = _color;
	speed = _speed;

	reset();
}

void Ball::Draw()
{
	DrawCircle(pos, radius, color);
}

void Ball::Move(float deltaTick)
{

	if (notLaunched)
	{
		pos = player->initialBallPos() - CL_Vec2f(0, radius);
		return;
	}

	if(verifyOutOfScreen()) {}
	else if(verifyHitPlayer()) {}
	else if(verifyHitBlocks()) {}

	pos.x += 0.01f * speed * dir.x * deltaTick;
	pos.y += 0.01f * speed * dir.y * deltaTick;
}

bool Ball::CollisionSphereRect(float minX, float maxX, float minY, float maxY, bool isPlayer)
{
	if (pos.y - radius < minY) return false;

	bool result = false;
	float distance;
	float closestX;
	float closestY;

	//remove the ball from inside the rect
	//while the ball stills inside the rect
	while ((pos.x <= maxX && pos.x >= minX) && (pos.y <= maxY && pos.y >= minY))
	{
		pos.x -= dir.x;
		pos.y -= dir.y;
		result = true;
	}

	// Find the closest point to the circle within the rectangle
	closestX = Clamp(pos.x, minX, maxX);
	closestY = Clamp(pos.y, minY, maxY);

	//if the ball was inside the rect, it already collides
	if (result)
	{
		CL_Vec2f closest(closestX, closestY);

		// If the distance is less than the circle's radius, an intersection occurs
		distance = closest.distance(pos);

		result = distance < radius;
	}

	if (result)
	{
		if (closestX == minX)
		{
			// topLeftEdge = top
			if (closestY == minY)
			{
				dir.mirror(CL_Vec2f(0, 1));
				if (isPlayer)
				{
					//TODO: move the ball in the angle
				}
				closestX -= radius;
				closestY -= radius;
			}
			// botLeftEdge = left
			else if (closestY == maxY)
			{
				dir.mirror(CL_Vec2f(-1, 0));
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
			// topRightEdge = top
			if (closestY == minY)
			{
				dir.mirror(CL_Vec2f(0, 1));
				if (isPlayer)
				{
					//TODO: move the ball in the angle
				}
				closestX += radius;
				closestY -= radius;
			}
			// botRightEdge = right
			else if (closestY == maxY)
			{
				dir.mirror(CL_Vec2f(1, 0));
				closestX += radius;
				closestY += radius;
			}
			// right
			else
			{
				dir.mirror(CL_Vec2f(1, 0));
				closestX += radius;
			}
		}
		else
		{			
			// bot
			if (closestY == maxY)
			{
				dir.mirror(CL_Vec2f(0, 1));
				closestY += radius;
			}
			// top
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

	return result;
}

float Ball::Clamp(float v, float lo, float hi)
{
	return (v < lo) ? lo : (hi < v) ? hi : v;
}
