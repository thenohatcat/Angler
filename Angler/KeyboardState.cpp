//Version: 0.1.12
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_12
#error KeyboardState.cpp: Wrong Version 0.1.12
#endif

#include "Keyboard.h"

using namespace Angler::Input;

KeyboardState::KeyboardState()
	: mAlt(false), mShift(false), mCtrl(false),
	mOldAlt(false), mOldShift(false), mOldCtrl(false), mNumKeysDown(0), mOldNumKeysDown(0)
{
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		mKeys[i] = mOldKeys[i] = false;
	}
}

KeyboardState::KeyboardState(KeyboardState &state)
	: mAlt(state.mAlt), mShift(state.mShift), mCtrl(state.mCtrl),
	mOldAlt(state.mOldAlt), mOldShift(state.mOldShift), mOldCtrl(state.mOldCtrl), 
	mNumKeysDown(state.mNumKeysDown), mOldNumKeysDown(state.mOldNumKeysDown)
{
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		mKeys[i] = state.mKeys[i];
		mOldKeys[i] = state.mOldKeys[i];
	}
}

void KeyboardState::pushState()
{
	for (int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		mOldKeys[i] = mKeys[i];
	}
	mOldAlt = mAlt;
	mOldShift = mOldAlt;
	mOldCtrl = mOldCtrl;
	mOldNumKeysDown = mNumKeysDown;
}

bool KeyboardState::isKeyDown(sf::Keyboard::Key key)
{
	return mKeys[key];
}

bool KeyboardState::wasKeyDown(sf::Keyboard::Key key)
{
	return mOldKeys[key];
}

bool KeyboardState::isAltDown()
{
	return mAlt;
}

bool KeyboardState::isShiftDown()
{
	return mShift;
}

bool KeyboardState::isCtrlDown()
{
	return mCtrl;
}

bool KeyboardState::wasAltDown()
{
	return mOldAlt;
}

bool KeyboardState::wasShiftDown()
{
	return mOldShift;		
}

bool KeyboardState::wasCtrlDown()
{
	return mOldCtrl;
}

int KeyboardState::getIsNumKeysDown()
{
	return mNumKeysDown;
}

int KeyboardState::getWasNumKeysDown()
{
	return mOldNumKeysDown;
}