#include "PlatformPrecomp.h"
#include "UI.h"

void UI::printLife()
{
	string sLifes = "x";
	myFont->DrawScaled(125, 30, sLifes, 2.5);
	sLifes = to_string(lifes);
	myFont->DrawScaled(165, 0, sLifes, 4);
	heart.BlitScaled(75, 50, CL_Vec2f(.15, .15));
}

void UI::printHighscore()
{
	string sHighscore = "HighScore";
	myFont->DrawAligned(512, 0, sHighscore, ALIGNMENT_UPPER_CENTER, 1.5);
	sHighscore = to_string(highscore);
	myFont->DrawAligned(512, 28, sHighscore, ALIGNMENT_UPPER_CENTER, 3);
}

void UI::printScore()
{
	string sScore = "Score";
	myFont->DrawAligned(850, 10, sScore, ALIGNMENT_UPPER_CENTER, 1);
	sScore = to_string(score);
	myFont->DrawAligned(850, 40, sScore, ALIGNMENT_UPPER_CENTER, 2);
}

void UI::Init(int _lifes)
{
	highscore = 0;
	lifes = _lifes;
	divColor = MAKE_RGBA(255, 255, 255, 255);

	myFont = new RTFont();
	myFont->Load("interface/font_trajan.rtfont");
	myFont->SetSmoothing(false);

	heart.LoadFile("interface/pixel-heart.rttex");
	heart.Bind();
}

void UI::Draw()
{
	// print div line
	DrawFilledRect(CL_Vec2f(-1, 97),CL_Vec2f(GetScreenSizeX() + 2, 3), divColor);
	printHighscore();
	printScore();
	printLife();
}