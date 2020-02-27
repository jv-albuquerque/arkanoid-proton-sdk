#include "PlatformPrecomp.h"
#include "Player.h"

void Player::verifyOutOfScreen()
{
	float leftLimit = GetScreenSizeX() - size.x;

	if (pos.x <= 0)
	{
		pos.x = 0;
	}
	else if (pos.x >= leftLimit)
	{
		pos.x = leftLimit;
	}
}

void Player::Init(CL_Vec2f _initialPos, CL_Vec2f _size, uint32 _color, float _speed)
{
	pos = _initialPos;
	size = _size;
	color = _color;
	speed = _speed;
}

void Player::Draw()
{
	DrawFilledRect(pos, size, color);
}

void Player::Update(float deltaTick)
{
	pos.x += 0.01f * speed * moveScale * deltaTick;

	verifyOutOfScreen();
}

void Player::OnArcadeInput(int vKey, eVirtualKeyInfo keyInfo)
{
	if (keyInfo == VIRTUAL_KEY_PRESS)
	{
		if (vKey == VIRTUAL_KEY_DIR_LEFT)
		{
			moveScale = -1;
			leftPressed = true;
		}
		else if (vKey == VIRTUAL_KEY_DIR_RIGHT)
		{
			moveScale = 1;
			rightPressed = true;
		}
	}
	else if (keyInfo == VIRTUAL_KEY_RELEASE)
	{
		if (vKey == VIRTUAL_KEY_DIR_LEFT)
			leftPressed = false;
		else if (vKey == VIRTUAL_KEY_DIR_RIGHT)
			rightPressed = false;

		if (!leftPressed && !rightPressed)
			moveScale = 0;
	}
}

