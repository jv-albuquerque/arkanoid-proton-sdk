#include "PlatformPrecomp.h"
#include "Block.h"

void Block::Init(CL_Vec2f _initialPos, CL_Vec2f _size, uint32 _color, int _hits)
{
	pos = _initialPos;
	size = _size;
	color = _color;
	hitsToDestroy = _hits;
}

void Block::Draw()
{
	DrawFilledRect(pos, size, color);
}

bool Block::Hit(int damage)
{
	hitsToDestroy -= damage;
	if (hitsToDestroy <= 0)
		return true;
	return false;
}
