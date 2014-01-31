//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

//MouseState
//Changelog:
//+ added	sf::Vector2i getPos
//+ added	sf::Vector2i getOldPos
//renamed	getX to getPosX
//renamed	getY to getPosY
//renamed	getOldX to getOldPosX
//renamed	getOldY to getOldPosY

//Mouse
//Changelog:
//added		changePos(sf::Vector2i)

#ifndef INC_MOUSE_H
#define INC_MOUSE_H

#ifdef ANGLER_0_1_1

#include <SFML\Window\Mouse.hpp>

namespace Angler
{
	namespace Input
	{
	class MouseState
	{
		public:
			friend class Mouse;

			MouseState();
			MouseState(MouseState &state);

			bool isButtonDown(sf::Mouse::Button button);
			bool wasButtonDown(sf::Mouse::Button button);

			int getPosX(), getPosY();
			sf::Vector2i getPos();
			int getOldPosX(), getOldPosY();
			sf::Vector2i getOldPos();

			int getWheel();
			int getOldWheel();

			void pushState();

		private:
			bool mButtons[sf::Mouse::Button::ButtonCount];
			bool mOldButtons[sf::Mouse::Button::ButtonCount];

			int mX, mY;
			int mOldX, mOldY;
			int mWheel;
			int mOldWheel;
		};

		class Mouse
		{
		public:
			MouseState getState();

			void buttonDown(sf::Mouse::Button button);
			void buttonUp(sf::Mouse::Button button);

			void wheelMoved(int delta);

			void changePos(sf::Vector2i pos);
			void changeX(int x);
			void changeY(int y);

			void pushState();
		private:
			MouseState mState;
		};
	}
}

#else
#error Mouse.h: Wrong Version 0.1.1
#endif

#endif