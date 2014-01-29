#include "Game.h"

#include <iostream>

Game::Game()
	: mWidth(800), mHeight(600), mSceneRoot(new Node()), mKeyboard(new Keyboard()),
	mMouse(new Mouse())
{

}

Game::~Game()
{
	mWindow->close();

	delete mGraphics;
	delete mWindow;
}

void Game::init()
{
	mWindow = new sf::RenderWindow(sf::VideoMode(mWidth, mHeight), mTitle, 
		sf::Style::Close);

	mGraphics = new Graphics(this);
}

void Game::loadContent()
{
	mLoadContent();
}

void Game::mResize(int width, int height)
{
	mWidth = width;
	mHeight = height;

	glViewport(0, 0, mWidth, mHeight);
}

void Game::run()
{
	mGameClock = sf::Clock();

	sf::Time oldTime = mGameClock.getElapsedTime();

	while (mWindow->isOpen())
	{
		sf::Time sftime = mGameClock.getElapsedTime();

		float time = sftime.asSeconds();
		float deltaTime = (sftime - oldTime).asSeconds();

		sf::Event event;
        while (mWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mWindow->close();
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
				mMouse->changeX(event.mouseButton.x);
				mMouse->changeY(event.mouseButton.y);
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				mMouse->buttonUp(event.mouseButton.button);
				mMouse->changeX(event.mouseButton.x);
				mMouse->changeY(event.mouseButton.y);
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				mMouse->changeX(event.mouseMove.x);
				mMouse->changeY(event.mouseMove.y);
			}
			else if (event.type == sf::Event::MouseWheelMoved)
			{
				mMouse->wheelMoved(event.mouseWheel.delta);
				mMouse->changeX(event.mouseMove.x);
				mMouse->changeY(event.mouseMove.y);
			}
        }

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float(mWidth) / float(mHeight)), 1, 0, 0.5, 10);

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

		mUpdate(time, deltaTime);
		mDraw(time, deltaTime);

		mWindow->display();
		
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