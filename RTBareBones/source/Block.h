#pragma once
class Block
{
private:
	CL_Vec2f pos;
	uint32 color;
	CL_Vec2f size;

public:
	virtual void Init(CL_Vec2f _initialPos, CL_Vec2f _size, uint32 _color);
	virtual void Draw();
	float* GetBox() { float p[] = { pos.x, pos.y, pos.x + size.x, pos.y + size.y }; return p; }
};

