#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "ImageHandler.h"

class HealthBar
{
private:
	Direction side; // Side the health bar is on
	Point startPoint; // Offset for the health bar
	int health; // Total player health out of 100
	int yellowWidth; // Current width of yellow bar
	int yellowDropCountdown; // Counts after being hit to see if yellow bar should decrease
	int yellowDeInc; // Yellow decreasing increment

public:
	HealthBar(Direction sideSet);
	void Draw(ImageHandler *img);
	void Update();
	void HitFor(int val);
	bool Dead();
	void Reset();
};

#endif