#pragma once
class Player
{
private:
	CL_Vec2f pos;
	uint32 color;
	CL_Vec2f size;
	float speed;
	bool leftPressed = false;
	bool rightPressed = false;
	float moveScale = 0;

	void verifyOutOfScreen();

public:
	virtual void Init(CL_Vec2f _initialPos, CL_Vec2f _size, uint32 _color, float _speed = 10);
	virtual void Draw();
	virtual void Update(float deltaTick);
	void OnArcadeInput(int vKey, eVirtualKeyInfo keyInfo);
	float* GetBox() { float p[] = { pos.x, pos.y, pos.x + size.x, pos.y + size.y }; return p; }
	float GetMoveScale() { return moveScale; }
};

