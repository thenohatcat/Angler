//Version: 0.1.3
//Author: Jakob Pipping
//Contributors:

#ifndef INC_KEYBOARD_H
#define INC_KEYBOARD_H

#ifdef ANGLER_0_1_3

#include <SFML\Window\Keyboard.hpp>

namespace Angler
{
	namespace Input
	{
		class KeyboardState
		{
		public:
			friend class Keyboard;

			KeyboardState();
			KeyboardState(KeyboardState &state);

			bool isKeyDown(sf::Keyboard::Key key);

			bool wasKeyDown(sf::Keyboard::Key key);

			//As a keyboard has multiple of these keys these values returns
			//if ANY of the certain keys are down, useful when there is no
			//need to know wich key specifically is pressed
			bool isAltDown(), isShiftDown(), isCtrlDown();
			bool wasAltDown(), wasShiftDown(), wasCtrlDown();

			//Pushes the current state into the old state, for use to detect
			//changes in state
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

			//Functions to update the current state
			void keyDown(sf::Keyboard::Key key, bool alt, bool shift, bool ctrl);
			void keyUp(sf::Keyboard::Key key, bool alt, bool shift, bool ctrl);

			//Wrapper for the internal KeyboardState::pushState
			void pushState();

		private:
			KeyboardState mState;
		};
	}
}

#else
#error Keyboard.h: Wrong Version 0.1.3
#endif

#endif