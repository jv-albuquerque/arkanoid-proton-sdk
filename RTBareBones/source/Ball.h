#ifndef BALL_H
#define BALL_H
#pragma once

#include "Player.h"
#include "Block.h"

class Ball
{
private:
	CL_Vec2f pos;
	CL_Vec2f dir;
	uint32 color;
	float radius;
	float speed;
	bool notLaunched;

	bool verifyOutOfScreen();
	bool verifyHitPlayer();
	bool verifyHitBlocks();
	void Move(float deltaTick);

	bool CollisionSphereRect(float minX, float maxX, float minY, float maxY, bool isPlayer = false);
	float Clamp(float v, float lo, float hi);

public:
	void Init(Player* _player, list<Block>* _blocks, float _radius, uint32 _color, float _speed = 10);
	virtual void Draw();
	virtual void Update(float deltaTick);
	void reset();
	void SetBlocks(list<Block>* _blocks) { blocks = _blocks; }
	CL_Vec2f GetPos() { return pos; }
	float GetRadius() { return radius; }
	void SetDirection(CL_Vec2f normal) { dir.mirror(normal); }
	void Launch();

private:
	Player* player;
	list<Block>* blocks;
};
#endif
