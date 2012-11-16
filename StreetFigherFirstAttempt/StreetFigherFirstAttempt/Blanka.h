#ifndef BLANKA_H
#define BLANKA_H

#include "Player.h"

class Blanka : public Player
{
private:

public:
	Blanka(Sprite walkRightAnimSet, Sprite standAnimSet, Sprite walkLeftAnimSet, Sprite punchAnimSet, Direction direcSet);
};

#endif