#pragma once
class Ball
{
private:
	CL_Vec2f pos;
	uint32 color;
	float radius;
	float speed;
	CL_Vec2f dir;

	void verifyOutOfScreen();
	void Move();

public:
	virtual void Init(CL_Vec2f _initialPos, float _radius, uint32 _color, float _speed = 10);
	virtual void Draw();
	virtual void Update(float deltaTick);
};

