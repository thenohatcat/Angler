//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_1
#error Game.cpp: Wrong Version 0.1.1
#endif

#include "Game.h"

#include <iostream>

Game::Game()
	: mWidth(800), mHeight(600)
{

}

Game::~Game()
{
	mGraphics->mWindow->close();

	delete mGraphics;
}

void Game::init()
{
	mGraphics = new Graphics(this, mNumLayers);
	mGraphics->createWindow(mWidth, mHeight, mTitle, false);

	mKeyboard = new Keyboard();
	mMouse = new Mouse();
	mSceneRoot = new Node();

	mInnerInit();
}

void Game::loadContent()
{
	mLoadContent();
}

void Game::mResize(int width, int height)
{
	mGraphics->resize(width, height);
}

void Game::run()
{
	mGameClock = sf::Clock();

	sf::Time oldTime = mGameClock.getElapsedTime();

	while (mGraphics->mWindow->isOpen())
	{
		sf::Time sftime = mGameClock.getElapsedTime();

		float time = sftime.asSeconds();
		float deltaTime = (sftime - oldTime).asSeconds();

		sf::Event event;
        while (mGraphics->mWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mGraphics->mWindow->close();
			else if (event.type == sf::Event::LostFocus)
				mFocused = false;
			else if (event.type == sf::Event::GainedFocus)
				mFocused = true;
			else if (event.type == sf::Event::Resized)
				mResize(event.size.width, event.size.height);
			else if (event.type == sf::Event::KeyPressed)
				mKeyboard->keyDown(event.key.code, event.key.alt, event.key.shift, event.key.control);
			else if (event.type == sf::Event::KeyReleased)
				mKeyboard->keyUp(event.key.code, event.key.alt, event.key.shift, event.key.control);
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				mMouse->buttonDown(event.mouseButton.button);
				mMouse->changePos(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				mMouse->buttonUp(event.mouseButton.button);
				mMouse->changePos(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				mMouse->changePos(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			}
			else if (event.type == sf::Event::MouseWheelMoved)
			{
				mMouse->wheelMoved(event.mouseWheel.delta);
				mMouse->changePos(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			}
        }

		mUpdate(time, deltaTime);
		mDraw(time, deltaTime);

		mGraphics->display();
		
		mKeyboard->pushState();
		mMouse->pushState();
		oldTime = sftime;
	}
}

KeyboardState Game::getKeyboardState()
{
	return mKeyboard->getState();
}

MouseState Game::getMouseState()
{
	return mMouse->getState();
}

void Game::loadTexture(sf::Texture* texture, const char *fileName)
{
	mGraphics->loadTexture(texture, fileName);
}

int Game::getWidth()
{
	return mGraphics->getWidth();
}

int Game::getHeight()
{
	return mGraphics->getHeight();
}