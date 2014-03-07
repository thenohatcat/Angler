//Version: 0.1.9
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_9
#error Keyboard.cpp: Wrong Version 0.1.9
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
	mState.mNumKeysDown++;
}

void Keyboard::keyUp(sf::Keyboard::Key key, bool alt, bool shift, bool ctrl)
{
	mState.mKeys[key] = false;
	mState.mAlt = alt;
	mState.mShift = shift;
	mState.mCtrl = ctrl;
	mState.mNumKeysDown--;
}