#include "Ryu.h"


Ryu::Ryu(Sprite (&animationSet)[TOTAL_PLAYER_ANIMATIONS], Direction direcSet)
	: Player(animationSet, direcSet, 0)
{
	Rect punchBox[5] = {Rect(0, 0, 0, 0), Rect(69, 12, 52, 20), Rect(69, 12, 52, 20), Rect(0, 0, 0, 0), Rect(0, 0, 0, 0)};
	std::copy(punchBox, punchBox+5, attackBoxes[PUNCHING]);

	Rect kickBox[6] = {Rect(0,0,0,0), Rect(0,0,0,0), Rect(84, 64, 38, 27), Rect(84, 64, 38, 28), Rect(0,0,0,0), Rect(0,0,0,0)};
	std::copy(kickBox, kickBox+6, attackBoxes[KICKING]);
}

bool Ryu::ThrowFireball()
{
	return State() == SPECIALING && CurrentFrame() == 6;
}

Point Ryu::FireballStart()
{
	return BasePoint() + Point(70, 25);
}