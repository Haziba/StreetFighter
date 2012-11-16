#ifndef PLAYER_H
#define PLAYER_H

#include "ImageHandler.h"
#include "Globals.h"
#include "InputHandler.h"
#include <iostream>

const int TOTAL_PLAYER_ANIMATIONS = 8;

enum PlayerStates
{
	STANDING = 0,
	WALKING_RIGHT = 1,
	WALKING_LEFT = 2,
	PUNCHING = 3,
	BEING_HIT_HIGH = 4,
	VICTORYING = 5,
	DIEING = 6,
	KICKING = 7,
};

enum PlayerAnimations
{
	STAND = 0,
	WALK_RIGHT = 1,
	WALK_LEFT = 2,
	PUNCH = 3,
	HIT_HIGH = 4,
	VICTORY = 5,
	DEATH = 6,
	KICK = 7,
};

class Player
{
private:
	Sprite animations[TOTAL_PLAYER_ANIMATIONS];

	Sprite * currentImage;

	PlayerStates state;
	Direction direc;

	Rect topHitBox;
	Rect bottomHitBox;

	Rect attackBox;
	bool attacking;

	void NextFrame();
	void ChangeImage(Sprite *nextImage);
	void RecenterImages();
	void CenterImage(Sprite *image, int x, int y);

	void UpdateHitBoxes();

	bool GettingHit();

	Point GetOriginPoint();

	void WalkRight(bool leftIsDown);
	void WalkLeft(bool rightIsDown);
	void Stand();
	void Punch();
	void Kick();

protected:
	Rect attackBoxes[TOTAL_PLAYER_ANIMATIONS][32];

public:
	Player(Sprite (&animationSet)[TOTAL_PLAYER_ANIMATIONS], Direction direcSet);
	void Draw(ImageHandler * img);
	void Update();

	void Input(InputHandler input);
	void ReleaseControl();

	bool CheckCollision(Rect attackBox);

	Rect AttackBox();
	bool Attacking();
	Point AttackEndPoint();

	void Win();
	void Die();
};

#endif