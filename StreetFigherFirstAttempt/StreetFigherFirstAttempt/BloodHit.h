#ifndef BLOODHIT_H
#define BLOODHIT_H

#include <Windows.h>
#include "ImageHandler.h"

class BloodHit
{
private:
	int x, y, xSpeed, ySpeed;
public:
	BloodHit();
	BloodHit(int xSet, int ySet);
	void Draw(ImageHandler *img);
	void Update();
	bool Active();
};

#endif