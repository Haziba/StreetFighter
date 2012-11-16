#include "WindowsHandler.h"


InputHandler WindowsHandler::input;

bool WindowsHandler::Initialise(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow, int width, int height, HDC &backHDCRet, HDC &bitmapHDCRet)
{
	RegisterMyWindow(hInstance);

   	if (!InitialiseMyWindow(hInstance, nCmdShow, width, height))
		return FALSE;
	
	setBuffers();

	backHDCRet = backHDC;
	bitmapHDCRet = bitmapHDC;

	return TRUE;
};

int WindowsHandler::Start(void (*update)(InputHandler), void (*draw)())
{
	Update = (update);
	Draw = (draw);

	while (TRUE)					
    {
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
		    if (msg.message==WM_QUIT)
				break;
			TranslateMessage (&msg);							
			DispatchMessage (&msg);
		}

		else
		{
			if (WaitFor(1000/ 18))
			{
				Draw();
				displayFrame();
				Update(input);
				input.Update();
			}

		}
    }

    releaseResources();
	return msg.wParam ;
}

void WindowsHandler::RegisterMyWindow(HINSTANCE hInstance)
{
    WNDCLASSEX  wcex;									

    wcex.cbSize        = sizeof (wcex);				
    wcex.style         = CS_HREDRAW | CS_VREDRAW;		
    wcex.lpfnWndProc   = WndProc;
    wcex.cbClsExtra    = 0;								
    wcex.cbWndExtra    = 0;								
    wcex.hInstance     = hInstance;						
    wcex.hIcon         = 0; 
    wcex.hCursor       = LoadCursor (NULL, IDC_ARROW);	
															
    wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
    wcex.lpszMenuName  = NULL;							
    wcex.lpszClassName = "FirstWindowClass";				
    wcex.hIconSm       = 0; 

	RegisterClassEx (&wcex);							
}


BOOL WindowsHandler::InitialiseMyWindow(HINSTANCE hInstance, int nCmdShow, int width, int height)
{
	HWND        hwnd;
	hwnd = CreateWindow ("FirstWindowClass",					
						 "Harry Boyes - Graphics Coursework",		  	
						 WS_OVERLAPPED | WS_DLGFRAME | WS_MINIMIZEBOX,	
						 40,
						 40,
						 width,			
						 height,			
						 NULL,					
						 NULL,					
						 hInstance,				
						 NULL);								
	if (!hwnd)
	{
		return FALSE;
	}

    ShowWindow (hwnd, nCmdShow);						
    UpdateWindow (hwnd);	
	ghwnd = hwnd;
	return TRUE;

}



BOOL WindowsHandler::WaitFor(unsigned long delay)
{
	static unsigned long clockStart = 0;
	unsigned long timePassed;
	unsigned long now = timeGetTime();

	timePassed = now - clockStart;
	if (timePassed >  delay)
	{
		clockStart = now;
		return TRUE;
	}
	else
		return FALSE;
}
	
			
LRESULT CALLBACK WindowsHandler::WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		case WM_CREATE:
			break;
		case WM_SIZE:
			break;
		case WM_KEYDOWN:
			input.UpdateKey(wParam, true);
			break;
		case WM_KEYUP:
			input.UpdateKey(wParam, false);
			break;
		case WM_MOUSEMOVE:
			input.SetMouse(LOWORD(lParam), HIWORD(lParam));
			break;
		case WM_PAINT:
		    break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc (hwnd, message, wParam, lParam);
}

void WindowsHandler::setBuffers()
{
	GetClientRect(ghwnd, &screenRect);	//creates rect based on window client area
	frontHDC = GetDC(ghwnd);			// Initialises front buffer device context (window)
	backHDC = CreateCompatibleDC(frontHDC);// sets up Back DC to be compatible with the front
	bitmapHDC=CreateCompatibleDC(backHDC);
	theOldFrontBitMap = CreateCompatibleBitmap(frontHDC, screenRect.right, 
		screenRect.bottom);		//creates bitmap compatible with the front buffer
    theOldBackBitMap = (HBITMAP)SelectObject(backHDC, theOldFrontBitMap);
								//creates bitmap compatible with the back buffer
	FillRect(backHDC, &screenRect, (HBRUSH)GetStockObject(0));	
}

void WindowsHandler::displayFrame()
{
		BitBlt(frontHDC, screenRect.left,screenRect.top, screenRect.right, 
		screenRect.bottom, backHDC, 0, 0, SRCCOPY);
		FillRect(backHDC, &screenRect, (HBRUSH)GetStockObject(0));	
}

void WindowsHandler::releaseResources()
{
	SelectObject(backHDC,theOldBackBitMap);
	DeleteDC(backHDC);
	DeleteDC(bitmapHDC);
	ReleaseDC(ghwnd,frontHDC);
}