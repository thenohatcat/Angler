#ifndef INC_MOUSE_H
#define INC_MOUSE_H

#include <SFML\Window\Mouse.hpp>

class MouseState
{
public:
	friend class Mouse;

	MouseState();
	MouseState(MouseState &state);

	bool isButtonDown(sf::Mouse::Button button);
	bool wasButtonDown(sf::Mouse::Button button);

	int getX(), getY();
	int getOldX(), getOldY();

	int getWheel();
	int getOldWheel();

	void pushState();

private:
	bool mButtons[sf::Mouse::Button::ButtonCount];
	bool mOldButtons[sf::Mouse::Button::ButtonCount];

	int mX, mY;
	int mOldX, mOldY;
	int mWheel;
	int mOldWheel;
};

class Mouse
{
public:
	MouseState getState();

	void buttonDown(sf::Mouse::Button button);
	void buttonUp(sf::Mouse::Button button);

	void wheelMoved(int delta);

	void changeX(int x);
	void changeY(int y);

	void pushState();
private:
	MouseState mState;
};

#endif