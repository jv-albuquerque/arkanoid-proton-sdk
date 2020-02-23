#pragma once


class MovebleObject : public BaseApp
{
private:
	CL_Vec2f pos;
	CL_Vec4f color;
	CL_Vec2f size;
	float speed;
	bool leftPressed = false;
	bool rightPressed = false;
	float moveScale = 0;

	uint32 makeRGBA(CL_Vec4f _color);
	void verifyOutOfScreen();

public:
	virtual void Init(CL_Vec2f _initialPos, CL_Vec2f _size, CL_Vec4f _color, float _speed = 10);
	virtual void Draw();
	virtual void Update(float deltaTick);
	void OnArcadeInput(VariantList* pVList);
};

