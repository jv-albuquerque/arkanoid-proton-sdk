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
	Surface heart;
	RTFont* myFont;

	void printLife();
	void printHighscore();
	void printScore();

public:
	virtual void Init(int _lifes);
	virtual void Draw();
};

#endif

