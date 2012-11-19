#ifndef GAME_H
#define GAME_H

#include "ImageHandler.h"
#include "InputHandler.h"
#include "Ryu.h"
#include "Chun.h"
#include "HealthBar.h"
#include "BloodHit.h"

class Game
{
private:
	Chun chun;
	Ryu ryu;

	HealthBar ryuHealth;
	HealthBar chunHealth;

	BloodHit blood[30];

	bool paused;

	bool fireballActive;
	Sprite fireball;

	void NewBloodAt(BloodHit (&blood)[30], Point attackEndPoint);
	bool TestHitBoxes(Player *attacker, Player *defender, HealthBar *defenderHealth, BloodHit (&blood)[30]);

public:
	Game(Sprite (&r)[TOTAL_PLAYER_ANIMATIONS], Sprite (&c)[TOTAL_PLAYER_ANIMATIONS], Sprite fireballSet);
	void Update(InputHandler input);
	void Draw(ImageHandler *img);
};

#endif