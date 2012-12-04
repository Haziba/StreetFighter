#include "Game.h"


Game::Game(Sprite (&r)[TOTAL_PLAYER_ANIMATIONS], Sprite (&c)[TOTAL_PLAYER_ANIMATIONS], Sprite fireballSet)
	: ryu(r, LEFT), chun(c, RIGHT), ryuHealth(LEFT), chunHealth(RIGHT), fireball(fireballSet), fireballActive(false), paused(true)
{}

void Game::Update(InputHandler input)
{
	if(!paused)
	{
		if(!(chunHealth.Dead() || ryuHealth.Dead()))
		{
			ryu.Input(input);
			chun.Input(input);
		}
		else
			if(input.IsPressed(0x52)) // R key pressed
			{
				ryu.Reset();
				chun.Reset();
				chunHealth.Reset();
				ryuHealth.Reset();
			}

		ryu.Update();
		chun.Update();
		
		TestHitBoxes(&ryu, &chun, &chunHealth, blood);
		TestHitBoxes(&chun, &ryu, &ryuHealth, blood);

		UpdateFireball();

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

	if(input.IsPressed(VK_RETURN))
		paused = !paused;
	if(input.IsPressed(VK_ESCAPE))
		PostQuitMessage(0);
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
	if(fireballActive)
		img->DrawSprite(fireball);
	if(ryuHealth.Dead())
		img->DrawSprite(CHUN_VICTORY_SPLASH);
	if(chunHealth.Dead())
		img->DrawSprite(RYU_VICTORY_SPLASH);
	if(paused)
		img->DrawSprite(PAUSE_OVERLAY);
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

	if(fireballActive)
		if(defender->CheckCollision(Rect(fireball.x + 55 + fireball.shiftX, fireball.y + fireball.shiftY, 24, 28)))
		{
			defenderHealth->HitFor(5);
			NewBloodAt(blood, Point(fireball.x + 79 + fireball.shiftX, fireball.y + 14 + fireball.shiftY));
			return true;
		}
}

void Game::UpdateFireball()
{
	if(fireballActive)
	{
		fireball.currentFrame++;
		if(fireball.currentFrame >= fireball.frames)
			fireball.currentFrame = 0;
		fireball.x += 20;
	}

	if(ryu.ThrowFireball())
	{
		fireballActive = true;
		Point fbStart = ryu.FireballStart();
		fireball.x = fbStart.X - fireball.shiftX;
		fireball.y = fbStart.Y - fireball.shiftY;
	}
}