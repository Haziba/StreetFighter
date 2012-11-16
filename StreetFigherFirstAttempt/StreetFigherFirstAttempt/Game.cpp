#include "Game.h"


Game::Game(Sprite (&r)[TOTAL_PLAYER_ANIMATIONS], Sprite (&c)[TOTAL_PLAYER_ANIMATIONS])
	: ryu(r, LEFT), chun(c, RIGHT), ryuHealth(LEFT), chunHealth(RIGHT), character(&ryu)
{}

void Game::Update(InputHandler input)
{
	if(!(chunHealth.Dead() || ryuHealth.Dead()))
		character->Input(input);

	if(true)
	{
		ryu.Update();
		chun.Update();
		
		TestHitBoxes(&ryu, &chun, &chunHealth, blood);
		TestHitBoxes(&chun, &ryu, &ryuHealth, blood);

		if(chunHealth.Dead())
		{
			ryu.Win();
			chun.Die();
		}
		if(ryuHealth.Dead())
		{
			chun.Win();
			ryu.Die();
		}
		
		ryuHealth.Update();
		chunHealth.Update();
		for(int i = 0; i < 30; i++)
			blood[i].Update();
	}

	//if(keys[VK_RETURN] && !oldKeys[VK_RETURN])
	//	paused = !paused;
	if(input.IsPressed(VK_ESCAPE))
		PostQuitMessage(0);
	if(input.IsPressed(VK_TAB))
	{
		character->ReleaseControl();
		if(character == &ryu)
			character = &chun;
		else
			character = &ryu;
	}
}

void Game::Draw(ImageHandler *img)
{
	img->DrawSprite(BACKGROUND);
	ryu.Draw(img);
	chun.Draw(img);
	ryuHealth.Draw(img);
	chunHealth.Draw(img);
	for(int i = 0; i < 30; i++)
		blood[i].Draw(img);
}

void Game::NewBloodAt(BloodHit (&blood)[30], Point attackEndPoint)
{
	int count = 5;
	for(int i = 0; i < 30; i++)
		if(!blood[i].Active())
		{
			blood[i] = BloodHit(attackEndPoint.X, attackEndPoint.Y);
			count--;
			if(count <= 0)
				return;
		}
}

bool Game::TestHitBoxes(Player *attacker, Player *defender, HealthBar *defenderHealth, BloodHit (&blood)[30])
{
	if(attacker->Attacking())
		if(defender->CheckCollision(attacker->AttackBox()))
		{
			defenderHealth->HitFor(5);
			NewBloodAt(blood, attacker->AttackEndPoint());
			return true;
		}
}