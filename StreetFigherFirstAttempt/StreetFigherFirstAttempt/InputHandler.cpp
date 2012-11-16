#include "InputHandler.h"

InputHandler::InputHandler() : mouseX(0), mouseY(0)
{};

void InputHandler::SetMouse(int x, int y)
{
	mouseX = x;
	mouseY = y;
};

int InputHandler::MouseX()
{
	return mouseX;
}

int InputHandler::MouseY()
{
	return mouseY;
}

void InputHandler::UpdateKey(int key, bool state)
{
	keys[key] = state;
}

void InputHandler::Update()
{
	std::copy(keys, keys+256, oldKeys);
}

bool InputHandler::IsDown(int key)
{
	return keys[key];
}

bool InputHandler::IsPressed(int key)
{
	return keys[key] && !oldKeys[key];
}

bool InputHandler::IsReleased(int key)
{
	return !keys[key] && oldKeys[key];
}