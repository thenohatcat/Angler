//Version: 0.1.3
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_3
#error Keyboard.cpp: Wrong Version 0.1.3
#endif

#include "Keyboard.h"

using namespace Angler::Input;

Keyboard::Keyboard()
{
	
}

KeyboardState Keyboard::getState()
{
	return KeyboardState(mState);
}

void Keyboard::pushState()
{
	mState.pushState();
}

void Keyboard::keyDown(sf::Keyboard::Key key, bool alt, bool shift, bool ctrl)
{
	mState.mKeys[key] = true;
	mState.mAlt = alt;
	mState.mShift = shift;
	mState.mCtrl = ctrl;
}

void Keyboard::keyUp(sf::Keyboard::Key key, bool alt, bool shift, bool ctrl)
{
	mState.mKeys[key] = false;
	mState.mAlt = alt;
	mState.mShift = shift;
	mState.mCtrl = ctrl;
}