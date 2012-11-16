#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H
#include <Windows.h>
#include <GdiPlus.h>

using namespace Gdiplus;

const int TOTAL_IMAGES = 22;

enum ImageName
{
	RYU_STAND=0,
	BACKGROUND=1,
	RYU_MOVE_RIGHT=2,
	RYU_MOVE_LEFT=3,
	RYU_PUNCH=4,
	BLANKA_STAND=5,
	CHUN_STAND=6,
	CHUN_WALK_LEFT=7,
	CHUN_WALK_RIGHT=8,
	CHUN_PUNCH=9,
	CHUN_HIT_HIGH=10,
	RYU_HIT_HIGH=11,
	HEALTH_BAR_OVERLAY=12,
	HEALTH_BAR_RED=13,
	HEALTH_BAR_YELLOW=14,
	BLOOD_DROP=15,
	RYU_VICTORY=16,
	CHUN_VICTORY=17,
	RYU_DEATH=18,
	CHUN_DEATH=19,
	RYU_KICK=20,
	CHUN_KICK=21,
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