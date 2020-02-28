#ifndef UI_H
#define UI_H

#pragma once
class UI
{
private:
	int lifes;
	int score;
	int highscore;
	uint32 divColor;

public:
	virtual void Init(int _lifes);
	virtual void Draw();
};

#endif

