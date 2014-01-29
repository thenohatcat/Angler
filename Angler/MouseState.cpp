#include "Mouse.h"

MouseState::MouseState()
	: mX(0), mY(0), mOldX(0), mOldY(0), mWheel(0), mOldWheel(0)
{
	for (int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
	{
		mOldButtons[i] = mButtons[i] = false;
	}
}

MouseState::MouseState(MouseState &state)
	: mX(state.mX), mY(state.mY), mOldX(state.mOldX), mOldY(state.mOldY), 
	mWheel(state.mWheel), mOldWheel(state.mOldWheel)
{
	for (int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
	{
		mButtons[i] = state.mButtons[i];
		mOldButtons[i] = state.mOldButtons[i];
	}
}

void MouseState::pushState()
{
	for (int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
	{
		mOldButtons[i] = mButtons[i];
	}

	mOldX = mX;
	mOldY = mY;
	mOldWheel = mWheel;
	//As the wheel only moves momentarily
	mWheel = 0;
}

bool MouseState::isButtonDown(sf::Mouse::Button button)
{
	return mButtons[button];
}

bool MouseState::wasButtonDown(sf::Mouse::Button button)
{
	return mOldButtons[button];
}

int MouseState::getX()
{
	return mX;
}

int MouseState::getY()
{
	return mY;
}

int MouseState::getOldX()
{
	return mOldX;
}

int MouseState::getOldY()
{
	return mOldY;
}

int MouseState::getWheel()
{
	return mWheel;
}

int MouseState::getOldWheel()
{
	return mOldWheel;
}