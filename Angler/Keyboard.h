//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef INC_KEYBOARD_H
#define INC_KEYBOARD_H

#ifdef ANGLER_0_1_1

#include <SFML\Window\Keyboard.hpp>

class KeyboardState
{
public:
	friend class Keyboard;

	KeyboardState();
	KeyboardState(KeyboardState &state);

	bool isKeyDown(sf::Keyboard::Key key);

	bool wasKeyDown(sf::Keyboard::Key key);

	bool isAltDown(), isShiftDown(), isCtrlDown();
	bool wasAltDown(), wasShiftDown(), wasCtrlDown();

	void pushState();

private:
	bool mKeys[sf::Keyboard::Key::KeyCount];
	bool mOldKeys[sf::Keyboard::Key::KeyCount];
	bool mAlt, mShift, mCtrl;
	bool mOldAlt, mOldShift, mOldCtrl;
};

class Keyboard
{
public:
	Keyboard();

	KeyboardState getState();

	void keyDown(sf::Keyboard::Key key, bool alt, bool shift, bool ctrl);
	void keyUp(sf::Keyboard::Key key, bool alt, bool shift, bool ctrl);

	void pushState();

private:
	KeyboardState mState;
};

#else
#error Keyboard.h: Wrong Version 0.1.1
#endif

#endif