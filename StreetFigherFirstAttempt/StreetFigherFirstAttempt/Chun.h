#ifndef CHUN_H
#define CHUN_H

#include "Player.h"

class Chun : public Player
{
public:
	Chun(Sprite (&animationSet)[TOTAL_PLAYER_ANIMATIONS], Direction direcSet);
};

#endif
