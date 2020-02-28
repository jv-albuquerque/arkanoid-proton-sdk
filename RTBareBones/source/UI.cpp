#include "PlatformPrecomp.h"
#include "UI.h"

void UI::Init(int _lifes)
{
	divColor = MAKE_RGBA(255, 255, 255, 255);
}

void UI::Draw()
{
	DrawFilledRect(CL_Vec2f(-1, 97),CL_Vec2f(GetScreenSizeX() + 2, 3), divColor);
}