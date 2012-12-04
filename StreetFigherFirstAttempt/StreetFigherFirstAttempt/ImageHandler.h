#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H
#include <Windows.h>
#include <GdiPlus.h>

using namespace Gdiplus;

const int TOTAL_IMAGES = 30;

enum ImageName
{
	RYU_STAND,
	BACKGROUND,
	RYU_MOVE_RIGHT,
	RYU_MOVE_LEFT,
	RYU_PUNCH,
	BLANKA_STAND,
	CHUN_STAND,
	CHUN_WALK_LEFT,
	CHUN_WALK_RIGHT,
	CHUN_PUNCH,
	CHUN_HIT_HIGH,
	RYU_HIT_HIGH,
	HEALTH_BAR_OVERLAY,
	HEALTH_BAR_RED,
	HEALTH_BAR_YELLOW,
	BLOOD_DROP,
	RYU_VICTORY,
	CHUN_VICTORY,
	RYU_DEATH,
	CHUN_DEATH,
	RYU_KICK,
	CHUN_KICK,
	PAUSE_OVERLAY,
	RYU_CROUCH,
	CHUN_CROUCH,
	RYU_SPECIAL,
	CHUN_SPECIAL,
	FIREBALL,
	CHUN_VICTORY_SPLASH,
	RYU_VICTORY_SPLASH
};

enum Direction
{
	RIGHT = 0,
	LEFT = 1,
};

struct Sprite	//struct for sprite position and image
{
	int x, y, width, height, frames, currentFrame, shiftX, shiftY;
	Image* bitmap;
};

class ImageHandler
{
private:
	HDC bitmapHDC, backHDC;
	Sprite images[TOTAL_IMAGES];

	GdiplusStartupInput gdi;
	ULONG_PTR gdiToken;
public:
	ImageHandler(HDC bitmapHdc, HDC back);
	~ImageHandler();
	bool LoadABitmap(WCHAR *szFileName, int imageName, int x, int y, int width, int height);
	bool LoadABitmap(WCHAR *szFileName, int imageName, int x, int y, int width, int height, int shiftX, int shiftY, int frames);
	void DrawSpriteInRectAt(int imageName, Rect innerRect, Point loc);
	void DrawSpriteInRect(int imageName, Rect rect);
	void DrawSprite(int imageName);
	void DrawSprite(Sprite sprite, bool flipped=false);
	void DrawSquare(Rect rect);

	Sprite GetSprite(int imageName);
};

#endif