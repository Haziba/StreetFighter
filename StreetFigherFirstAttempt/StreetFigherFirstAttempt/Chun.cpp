#include "Chun.h"


Chun::Chun(Sprite (&animationSet)[TOTAL_PLAYER_ANIMATIONS], Direction direcSet)
	: Player(animationSet, direcSet, 1)
{
	Rect punchBox[5] = {Rect(0, 0, 0, 0), Rect(27, 9, 39, 17), Rect(35, 9, 39, 17), Rect(27, 9, 39, 17), Rect(0, 0, 0, 0)};
	std::copy(punchBox, punchBox+5, attackBoxes[PUNCHING]);

	Rect kickBox[11] = {Rect(0, 0, 0, 0), Rect(0, 0, 0, 0), Rect(43, 56, 37, 17), Rect(43, 56, 30, 26), Rect(43, 56, 31, 21), Rect(42, 69, 16, 26), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0)};
	std::copy(kickBox, kickBox+11, attackBoxes[KICKING]);

	Rect specialBox[41] = {Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(102,25,52,49), Rect(102,25,63,46), Rect(102,25,62,48), Rect(112,26,55,45), Rect(123,29,55,39), Rect(121,27,62,46), Rect(121,28,71,41), Rect(140,24,58,50), Rect(133,28,74,45), Rect(126,24,84,50), Rect(141,29,80,43), Rect(147,27,79,45), Rect(146,30,88,37), Rect(163,27,77,44), Rect(168,32,80,38), Rect(164,32,89,38), Rect(183,28,69,42), Rect(190,30,63,40), Rect(186,28,82,44), Rect(189,34,83,34), Rect(184,34,92,32), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0), Rect(0,0,0,0)};
	std::copy(specialBox, specialBox+41, attackBoxes[SPECIALING]);
}
