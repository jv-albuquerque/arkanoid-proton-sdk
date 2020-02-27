#include "PlatformPrecomp.h"
#include "Block.h"

void Block::Init(CL_Vec2f _initialPos, CL_Vec2f _size, uint32 _color)
{
	pos = _initialPos;
	size = _size;
	color = _color;
}

void Block::Draw()
{
	DrawFilledRect(pos, size, color);
}
