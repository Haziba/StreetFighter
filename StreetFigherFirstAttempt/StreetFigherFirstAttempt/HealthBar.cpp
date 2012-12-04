#include "HealthBar.h"


HealthBar::HealthBar(Direction sideSet) : side(sideSet), health(100), yellowWidth(200), yellowDropCountdown(0), yellowDeInc(0)
{
	if(sideSet == LEFT)
	{
		startPoint = Point(5, 5);
	}
	else
	{
		startPoint = Point(247, 5);
	}
}

void HealthBar::Draw(ImageHandler *img)
{
	int yellowOffset = (200-yellowWidth);
	int redOffset = ((100-health)*2);
	if(side == RIGHT)
	{
		img->DrawSpriteInRectAt(HEALTH_BAR_YELLOW, Rect(11+min(200-yellowWidth, 7)+(200-yellowWidth), 0, 207-(200-yellowWidth), 15), startPoint); 
		img->DrawSpriteInRectAt(HEALTH_BAR_RED, Rect(11+min(redOffset, 7)+redOffset, 0, 207 - redOffset, 15), startPoint);
	}
	else
	{	
		img->DrawSpriteInRectAt(HEALTH_BAR_YELLOW, Rect(max(0, 7-(200-yellowWidth)), 0, 207-(200-yellowWidth), 15), startPoint+Point(yellowOffset, 0)); 
		img->DrawSpriteInRectAt(HEALTH_BAR_RED, Rect(max(0, 7-redOffset), 0, 207-redOffset, 15), startPoint+Point(redOffset, 0));
	}
	img->DrawSpriteInRectAt(HEALTH_BAR_OVERLAY, Rect(0, 0, 209, 15), startPoint);
}

void HealthBar::Update()
{
	if(yellowDropCountdown > 0)
	{
		yellowDropCountdown--;
		if(yellowDropCountdown == 0)
			yellowDeInc = max((yellowWidth-(2*health)) / 12, 1);
	}
	yellowWidth -= yellowDeInc;
	if(yellowWidth <= health*2)
		yellowDeInc = 0;
}

void HealthBar::HitFor(int val)
{
	health -= val;
	yellowDropCountdown = 18;
	yellowDeInc = 0;
}

bool HealthBar::Dead()
{
	return health <= 0;
}

void HealthBar::Reset()
{
	health = 100;
	yellowWidth = 200;
	yellowDropCountdown = 0;
	yellowDeInc = 0;
}