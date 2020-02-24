#pragma once
class Object
{
protected:
	CL_Vec2f pos;
	CL_Vec4f color;
	CL_Vec2f size;
	float speed;

	uint32 makeRGBA(CL_Vec4f _color);

public:
	virtual void Init(CL_Vec2f _initialPos, CL_Vec2f _size, CL_Vec4f _color, float _speed = 0) = 0;
	virtual void Draw() = 0;
	virtual void Update(float deltaTick) = 0;
	virtual void OnArcadeInput(VariantList* pVList) = 0;
};

