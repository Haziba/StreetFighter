#include "BloodHit.h"

BloodHit::BloodHit() : y(500)
{
}

BloodHit::BloodHit(int xSet, int ySet) : x(xSet), y(ySet), xSpeed(rand() % 16 - 8), ySpeed(-5 - rand() % 3)
{
}

void BloodHit::Draw(ImageHandler *img)
{
	if(Active())
		img->DrawSpriteInRectAt(BLOOD_DROP, Rect(0, 0, 5, 5), Point(x, y));
}

void BloodHit::Update()
{
	if(Active())
	{
		x += xSpeed;
		y += ySpeed;
		if(xSpeed < 0) xSpeed++;
		if(xSpeed > 0) xSpeed--;
		ySpeed++;
	}
}

bool BloodHit::Active()
{
	return y <= 207;
}