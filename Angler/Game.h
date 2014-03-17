//Version: 0.1.11
//Author: Jakob Pipping
//Contributors: 

#ifndef INC_GAME_H
#define INC_GAME_H

#ifdef ANGLER_0_1_11

#include "Graphics.h"
#include "Sound.h"
#include "Mechanics.h"

#include "Keyboard.h"
#include "Mouse.h"

namespace Angler
{
	class Node;

	class Game
	{
	public:
		Game();
		~Game();

		//Initializes the game, and calls mInit (for derived)
		void init();

		//Loads content
		void loadContent();

		//Starts the game logic and main loop
		void run();

		//Wrapper for the current keyboard and mouse states
		Angler::Input::KeyboardState getKeyboardState();
		Angler::Input::MouseState getMouseState();

		//Wrapper for the same functions in GraphicsEngine
		int getWidth(), getHeight();

		//Wrapper for the same function in GraphicsEngine
		void loadTexture(sf::Texture* texture, const char* fileName);

		//Wraps the close in Graphics and does some game specific code
		void close();

		//Event handling
		virtual void throwEvent(int type, ... ) = 0;

		Angler::Graphics::GraphicsEngine *getGraphics();

		Angler::Sound::SoundEngine *getSound();

		Angler::Mechanics::MechanicsEngine *getMechanics();

		void setCursorVisible(bool visible);

		//Event IDs
		typedef enum
		{
			Collide
		} Events;

	protected:
		//Pointer to current graphics context
		Angler::Graphics::GraphicsEngine* mGraphics;
		//Pointer to current sound context
		Angler::Sound::SoundEngine* mSound;
		//Pointer to current mechanics context
		Angler::Mechanics::MechanicsEngine *mMechanics;
		//The root node of the current scene
		Node* mSceneRoot;
		Angler::Input::Keyboard* mKeyboard;
		Angler::Input::Mouse* mMouse;

		//Inner draw function, virtual
		virtual void mDraw(float time, float deltaTime) = 0;
		virtual void mUpdate(float time, float deltaTime) = 0;

		//Inner load content
		virtual void mLoadContent() = 0;

		//Inner init
		virtual void mInit() = 0;

		int mWidth;
		int mHeight;

		//Time elapsed since start functions
		float mGetTime();
		sf::Clock mGameClock;

		const char *mTitle;
		int mNumLayers;
		//If the window is currently the focus of the system
		bool mFocused;

	private:
		//Wrapper for the same function in GraphicsEngine, 
		//not used to change size of the window
		void mResize(int width, int height);
	};
}

#else
#error Game.h: Wrong Version 0.1.11
#endif

#endif