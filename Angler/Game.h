//Version: 0.1.1
//Author: Jakob Pipping
//Contributors: 

//Changelog:
//* added mInnerInit() to init()
//* moved some graphics code from Game::run() to Graphics::begin()
//* moved window handling to Graphics
//
//+ added		loadTexture(sf::Texture*, const char*)
//- removed		sf::RenderWindow* mWindow
//+ added		int getWidth()
//+ added		int getHeight()

//Bugs discovered:
//Bug-Angler-J-0001 Mouse position stored incorrectly

//Bugs solved:
//Bug-Angler-J-0001 Mouse position stored incorrectly
//* Solution: Changed update code to use the correct update format in the SFML event loop

#ifndef INC_GAME_H
#define INC_GAME_H

#ifdef ANGLER_0_1_1

#include "Graphics.h"
#include "Node.h"

#include "Keyboard.h"
#include "Mouse.h"

namespace Angler
{
	class Game
	{
	public:
		Game();
		~Game();

		void init();

		void loadContent();

		void run();

		Angler::Input::KeyboardState getKeyboardState();
		Angler::Input::MouseState getMouseState();

		int getWidth(), getHeight();

		void loadTexture(sf::Texture* texture, const char* fileName);

	protected:
		Angler::Graphics::GraphicsEngine* mGraphics;
		Node* mSceneRoot;
		Angler::Input::Keyboard* mKeyboard;
		Angler::Input::Mouse* mMouse;

		virtual void mDraw(float time, float deltaTime) = 0;
		virtual void mUpdate(float time, float deltaTime) = 0;

		virtual void mLoadContent() = 0;

		virtual void mInnerInit() = 0;

		int mWidth;
		int mHeight;

		float mGetTime();
		sf::Clock mGameClock;

		const char *mTitle;
		int mNumLayers;
		bool mFocused;

	private:
		void mResize(int width, int height);
	};
}

#else
#error Game.h: Wrong Version 0.1.1
#endif

#endif