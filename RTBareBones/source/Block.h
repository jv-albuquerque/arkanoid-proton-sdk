#ifndef BLOCK_H
#define BLOCK_H
#pragma once

class Block
{
private:
	CL_Vec2f pos;
	uint32 color;
	CL_Vec2f size;
	int hitsToDestroy;

public:
	virtual void Init(CL_Vec2f _initialPos, CL_Vec2f _size, uint32 _color, int _hits);
	virtual void Draw();
	float* GetBox() { float p[] = { pos.x, pos.y, pos.x + size.x, pos.y + size.y }; return p; }
	bool Hit(int damage);
};
#endif

