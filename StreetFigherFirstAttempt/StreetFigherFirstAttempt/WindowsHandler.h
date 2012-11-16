#ifndef WINDOWSHANDLER_H
#define WINDOWSHANDLER_H

#include <windows.h>
#include "InputHandler.h"

class WindowsHandler
{
private:
	void RegisterMyWindow(HINSTANCE hInstance);
	BOOL InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow, int width, int height);
	BOOL WaitFor(unsigned long delay);
	static LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void setBuffers();
	void displayFrame();
	void releaseResources();

	HBITMAP	theOldFrontBitMap, theOldBackBitMap;
	HWND ghwnd;
	RECT screenRect;
	HDC backHDC, bitmapHDC, frontHDC;
    MSG msg;
	static InputHandler input;

	void (*Update)(InputHandler);
	void (*Draw)();

public:
	bool Initialise(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow, int width, int height, HDC &backHDCRet, HDC &bitmapHDCRet);
	int Start(void (*update)(InputHandler), void (*draw)());
};

#endif