#pragma once

#include "PlatformPrecomp.h"

class Object
{
public:
	virtual void Init(CL_Vec2f _initialPos, CL_Vec2f _size, uint32 _color, float _speed = 0) = 0;
	virtual void Draw() = 0;
	virtual void Update(float deltaTick) = 0;
	virtual void OnArcadeInput(VariantList* pVList) = 0;
};

