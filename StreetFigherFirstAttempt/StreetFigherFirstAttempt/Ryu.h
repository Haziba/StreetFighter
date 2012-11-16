#ifndef RYU_H
#define RYU_H

#include "Player.h"

class Ryu : public Player
{
private:

public:
	Ryu(Sprite (&animationSet)[TOTAL_PLAYER_ANIMATIONS], Direction direcSet);
};

#endif