#include "PlatformPrecomp.h"
#include "MovebleObject.h"

uint32 MovebleObject::makeRGBA(CL_Vec4f _color)
{
	return MAKE_RGBA(_color.r, _color.g, _color.b, _color.a);
}

void MovebleObject::verifyOutOfScreen()
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

void MovebleObject::Init(CL_Vec2f _initialPos, CL_Vec2f _size, CL_Vec4f _color, float _speed)
{
	BaseApp::Init();
	pos = _initialPos;
	size = _size;
	color = _color;
	speed = _speed;
}

void MovebleObject::Draw()
{
	DrawFilledRect(pos, size, makeRGBA(color));
}

void MovebleObject::Update(float deltaTick)
{
	GetBaseApp()->m_sig_arcade_input.connect(1, boost::bind(&MovebleObject::OnArcadeInput, this, _1));

	pos.x += 0.01f * speed * moveScale* deltaTick;

	LogMsg("%f", deltaTick);

	verifyOutOfScreen();
}

void MovebleObject::OnArcadeInput(VariantList* pVList)
{
	int vKey = pVList->Get(0).GetUINT32();
	eVirtualKeyInfo keyInfo = (eVirtualKeyInfo)pVList->Get(1).GetUINT32();


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

		if(!leftPressed && !rightPressed)
			moveScale = 0;
	}
}
