#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>

class InputHandler
{
private:
	int mouseX, mouseY;
	bool keys[256], oldKeys[256];
public:
	InputHandler();
	void SetMouse(int x, int y);
	int MouseX();
	int MouseY();
	void UpdateKey(int key, bool state);
	void Update();
	bool IsDown(int key);
	bool IsPressed(int key);
	bool IsReleased(int key);
};

#endif