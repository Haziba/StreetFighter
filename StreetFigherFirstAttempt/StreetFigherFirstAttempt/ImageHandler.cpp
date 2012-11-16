#include "ImageHandler.h"


ImageHandler::ImageHandler(HDC bitmapHDCSet, HDC backHDCSet): bitmapHDC(bitmapHDCSet), backHDC(backHDCSet)
{
	GdiplusStartup(&gdiToken, &gdi, NULL);
}

bool ImageHandler::LoadABitmap(WCHAR *szFileName, int imageName, int x, int y, int width, int height)
{
	return LoadABitmap(szFileName, imageName, x, y, width, height, 0, 0, 0);
}

bool ImageHandler::LoadABitmap(WCHAR *szFileName, int imageName, int x, int y, int width, int height, int shiftX, int shiftY, int frames)
{
	images[imageName].bitmap = new Image(szFileName);//(HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	images[imageName].x = x;
	images[imageName].y = y;
	images[imageName].width = width;
	images[imageName].height = height;
	images[imageName].frames = frames;
	images[imageName].shiftX = shiftX;
	images[imageName].shiftY = shiftY;
	images[imageName].currentFrame = 0;
	return !!(images[imageName].bitmap);
}

void ImageHandler::DrawSpriteInRectAt(int imageName, Rect innerRect, Point loc)
{
	Rect rect(images[imageName].x + loc.X, images[imageName].y + loc.Y, innerRect.Width, innerRect.Height);
	Graphics grpx(backHDC);
	grpx.DrawImage(images[imageName].bitmap, rect, innerRect.X, innerRect.Y, innerRect.Width, innerRect.Height, UnitPixel, NULL, NULL, NULL);
}

void ImageHandler::DrawSpriteInRect(int imageName, Rect innerRect)
{
	DrawSpriteInRectAt(imageName, innerRect, Point(0, 0));
}

void ImageHandler::DrawSprite(int imageName)
{
	DrawSpriteInRect(imageName, Rect(images[imageName].width * images[imageName].currentFrame, 0, images[imageName].width, images[imageName].height));
}

void ImageHandler::DrawSprite(Sprite image, bool flipped)
{
	Rect rect(image.x, image.y, image.width, image.height);
	Graphics grpx(backHDC);
	grpx.DrawImage(image.bitmap, rect, image.width * (flipped ? (image.frames) - image.currentFrame : image.currentFrame), 0, image.width, image.height, UnitPixel, NULL, NULL, NULL);
}

void ImageHandler::DrawSquare(Rect rect)
{
	Pen blackPen(Color(255, 0, 0, 0), 3);
	Graphics grpx(backHDC);
	grpx.DrawRectangle(&blackPen, rect);
}

Sprite ImageHandler::GetSprite(int imageName)
{
	return images[imageName];
}

ImageHandler::~ImageHandler()
{
	GdiplusShutdown(gdiToken);
}