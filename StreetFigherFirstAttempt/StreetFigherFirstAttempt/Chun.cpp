#include "Chun.h"


Chun::Chun(Sprite (&animationSet)[TOTAL_PLAYER_ANIMATIONS], Direction direcSet)
	: Player(animationSet, direcSet)
{
	Rect punchBox[5] = {Rect(0, 0, 0, 0), Rect(77, 9, 39, 17), Rect(85, 9, 39, 17), Rect(77, 9, 39, 17), Rect(0, 0, 0, 0)};
	std::copy(punchBox, punchBox+5, attackBoxes[PUNCHING]);

	Rect kickBox[11] = {Rect(0, 0, 0, 0), Rect(0, 0, 0, 0), Rect(93, 56, 37, 17), Rect(93, 56, 30, 26), Rect(93, 56, 31, 21), Rect(92, 69, 16, 26), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0)};
	std::copy(kickBox, kickBox+11, attackBoxes[KICKING]);
}
