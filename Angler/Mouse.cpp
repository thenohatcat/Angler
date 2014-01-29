#include "Mouse.h"

MouseState Mouse::getState()
{
	return MouseState(mState);
}

void Mouse::pushState()
{
	mState.pushState();
}

void Mouse::buttonDown(sf::Mouse::Button button)
{
	mState.mButtons[button] = true;
}

void Mouse::buttonUp(sf::Mouse::Button button)
{
	mState.mButtons[button] = false;
}

void Mouse::changeX(int x)
{
	mState.mX = x;
}

void Mouse::changeY(int y)
{
	mState.mY = y;
}

void Mouse::wheelMoved(int delta)
{
	mState.mWheel = delta;
}