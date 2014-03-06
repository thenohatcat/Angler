//Version: 0.1.9
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_9
#error Game.cpp: Wrong Version 0.1.9
#endif

#include "Game.h"

#include "Node.h"

#include <iostream>

#include "Keyboard.h"

using namespace Angler;
using namespace Angler::Graphics;
using namespace Angler::Mechanics;
using namespace Angler::Sound;
using namespace Angler::Input;

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
	//Initializes the graphics engine
	mGraphics = new GraphicsEngine(this);
	mGraphics->createWindow(mWidth, mHeight, mTitle, false);

	mMechanics = new MechanicsEngine(this);

	mSound = new SoundEngine(this);

	mKeyboard = new Keyboard();
	mMouse = new Mouse();
	mSceneRoot = new Node(0);

	//Runs the virtual inner init for derived
	mInit();
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
	//Initializes the clock at zero time of the program
	mGameClock = sf::Clock();

	//The time used to calculate time difference between frames
	sf::Time oldTime = mGameClock.getElapsedTime();

	std::cout << "Angler starting..." << std::endl;

	while (mGraphics->mWindow->isOpen())
	{
		//Current elapsed time (in sf::Time format)
		sf::Time sftime = mGameClock.getElapsedTime();

		//and in float format in seconds
		float time = sftime.asSeconds();
		//Time since last frame in seconds
		float deltaTime = (sftime - oldTime).asSeconds();

		//Handles SFML events
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
				mMouse->changePos(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			}
			else if (event.type == sf::Event::MouseWheelMoved)
			{
				mMouse->wheelMoved(event.mouseWheel.delta);
				mMouse->changePos(sf::Vector2i(event.mouseWheel.x, event.mouseWheel.y));
			}
        }

		mSceneRoot->update(this, time, deltaTime);		
		mSound->update(time, deltaTime);

		mUpdate(time, deltaTime);
		mDraw(time, deltaTime);

		mGraphics->display();
		
		//Pushes the states of the keyboard and mouse
		mKeyboard->pushState();
		mMouse->pushState();
		//Updates the old time with the beginning of the frame
		oldTime = sftime;
	}
}

GraphicsEngine *Game::getGraphics()
{
	return mGraphics;
}

SoundEngine *Game::getSound()
{
	return mSound;
}

MechanicsEngine *Game::getMechanics()
{
	return mMechanics;
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

void Game::close()
{
	mGraphics->close();
}