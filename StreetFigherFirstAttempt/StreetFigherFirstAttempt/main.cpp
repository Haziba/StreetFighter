//Windows Example Code
//Paul Robertson 2012

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include "Globals.h"
#include "WindowsHandler.h"
#include "ImageHandler.h"
#include "InputHandler.h"
#include "Game.h"

ImageHandler *img;
WindowsHandler window;
Game *game;



int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int nCmdShow)			
{
	HDC backHDC, bitmapHDC;
	if(!window.Initialise(hInstance, hPrevInstance, szCmdLine, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT, backHDC, bitmapHDC))
		return 0;

	void Update(InputHandler);
	void Draw();

	ImageHandler imgSet(bitmapHDC, backHDC);
	
	imgSet.LoadABitmap(L"Images/RyuStand.png", RYU_STAND, 20, 60, 78, 111, 0, 0, 9);
	imgSet.LoadABitmap(L"Images/RyuWalkRight.png", RYU_MOVE_RIGHT, 20, 60, 112, 113, -20, 0, 10);
	imgSet.LoadABitmap(L"Images/RyuWalkLeft.png", RYU_MOVE_LEFT, 20, 60, 112, 113, -20, 0, 10);
	imgSet.LoadABitmap(L"Images/RyuPunch.png", RYU_PUNCH, 20, 60, 121, 107, 0, 4, 4);
	imgSet.LoadABitmap(L"Images/RyuHitHigh.png", RYU_HIT_HIGH, 20, 60, 142, 112, -40, -2, 3);
	imgSet.LoadABitmap(L"Images/RyuVictory.png", RYU_VICTORY, 20, 60, 84, 109, 0, 0, 20);
	imgSet.LoadABitmap(L"Images/RyuDeath.png", RYU_DEATH, 20, 60, 177, 113, 0, 0, 16);
	imgSet.LoadABitmap(L"Images/RyuKick.png", RYU_KICK, 20, 60, 122, 105, 0, 6, 5);
	imgSet.LoadABitmap(L"Images/RyuCrouch.png", RYU_CROUCH, 20, 60, 87, 73, 0, 39, 4);
	imgSet.LoadABitmap(L"Images/RyuSpecial.png", RYU_SPECIAL, 20, 60, 136, 104, 0, 7, 13);
	
	imgSet.LoadABitmap(L"Images/ChunStand.png", CHUN_STAND, 350, 70, 83, 101, 0, 0, 19);
	imgSet.LoadABitmap(L"Images/ChunWalkLeft.png", CHUN_WALK_RIGHT, 350, 70, 111, 102, -20, 0, 31);
	imgSet.LoadABitmap(L"Images/ChunWalkRight.png", CHUN_WALK_LEFT, 350, 70, 110, 102, -20, 0, 31);
	imgSet.LoadABitmap(L"Images/ChunPunch.png", CHUN_PUNCH, 350, 70, 116, 104, 0, -2, 4);
	imgSet.LoadABitmap(L"Images/ChunHitHigh.png", CHUN_HIT_HIGH, 350, 70, 138, 106, -40, -4, 2);
	imgSet.LoadABitmap(L"Images/ChunVictory.png", CHUN_VICTORY, 20, 60, 121, 115, 0, -15, 20);
	imgSet.LoadABitmap(L"Images/ChunDeath.png", CHUN_DEATH, 20, 60, 167, 109, -60, 0, 15);
	imgSet.LoadABitmap(L"Images/ChunKick.png", CHUN_KICK, 20, 60, 131, 105, 5, -6, 10);
	imgSet.LoadABitmap(L"Images/ChunCrouch.png", CHUN_CROUCH, 20, 60, 99, 63, -14, 40, 15);
	imgSet.LoadABitmap(L"Images/ChunSpecial.png", CHUN_SPECIAL, 20, 60, 279, 114, -30, -13, 40);
	
	imgSet.LoadABitmap(L"Images/Background.png", BACKGROUND, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	imgSet.LoadABitmap(L"Images/PauseOverlay.png", PAUSE_OVERLAY, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	imgSet.LoadABitmap(L"Images/HealthBarOverlay.png", HEALTH_BAR_OVERLAY, 0, 0, 207, 15);
	imgSet.LoadABitmap(L"Images/HealthBarRed.png", HEALTH_BAR_RED, 0, 0, 216, 15);
	imgSet.LoadABitmap(L"Images/HealthBarYellow.png", HEALTH_BAR_YELLOW, 0, 0, 216, 15);
	
	imgSet.LoadABitmap(L"Images/BloodDrop.png", BLOOD_DROP, 0, 0, 5, 5);
	imgSet.LoadABitmap(L"Images/Fireball.png", FIREBALL, 0, 0, 384, 224, 146, 72, 8);

	Sprite r[TOTAL_PLAYER_ANIMATIONS] = {imgSet.GetSprite(RYU_STAND),  imgSet.GetSprite(RYU_MOVE_RIGHT),  imgSet.GetSprite(RYU_MOVE_LEFT),  imgSet.GetSprite(RYU_PUNCH),  imgSet.GetSprite(RYU_HIT_HIGH),  imgSet.GetSprite(RYU_VICTORY),  imgSet.GetSprite(RYU_DEATH),  imgSet.GetSprite(RYU_KICK),  imgSet.GetSprite(RYU_CROUCH), imgSet.GetSprite(RYU_SPECIAL)};
	Sprite c[TOTAL_PLAYER_ANIMATIONS] = {imgSet.GetSprite(CHUN_STAND), imgSet.GetSprite(CHUN_WALK_RIGHT), imgSet.GetSprite(CHUN_WALK_LEFT), imgSet.GetSprite(CHUN_PUNCH), imgSet.GetSprite(CHUN_HIT_HIGH), imgSet.GetSprite(CHUN_VICTORY), imgSet.GetSprite(CHUN_DEATH), imgSet.GetSprite(CHUN_KICK), imgSet.GetSprite(CHUN_CROUCH), imgSet.GetSprite(CHUN_SPECIAL)};

	img = &imgSet;
	game = &Game(r,c,imgSet.GetSprite(FIREBALL));


	return window.Start(Update, Draw);
}

void Update(InputHandler input)
{
	game->Update(input);
}

void Draw()
{
	game->Draw(img);
}