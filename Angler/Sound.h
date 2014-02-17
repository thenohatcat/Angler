//Version: 0.1.7
//Author: Oskar Engblad
//Contributors: Jakob Pipping

#ifndef INC_SOUND_H
#define INC_SOUND_H

#ifdef ANGLER_0_1_7

#include <SFML\Audio\Sound.hpp>
#include <list>

namespace Angler
{
	class Game;

	namespace Sound	
	{
		class SoundElement
		{
		public:
			SoundElement(sf::Sound *s, float start, float end,
				bool loop);

			bool isAlive();

			void play();
			void stop();
			void pause();

			void update(float time, float deltaTime);

			sf::Sound *getSound();

		private:
			sf::Sound *mSound;
			float mStart, mEnd;
			bool mLoop;
			bool mIsAlive;
		};

		class SoundEngine final
		{
		public:
			SoundEngine(Game *parent);

			bool playSound(sf::Sound *s, bool hard = true, 
				float start = -1, float end = -1, bool loop = false);

			void stopSound(sf::Sound *s);
			void pauseSound(sf::Sound *s);
			float getVolume(sf::Sound *s);
			void setVolume(sf::Sound *s, float x);
			int getStatus(sf::Sound *s);
			float getPosition(sf::Sound *s);
			void setPosition(sf::Sound *s, float x);
			void crossfade(sf::Sound *s1, float t, sf::Sound *s2, float v);

			void update(float time, float deltaTime);

		private:
			Game *mParent;
			std::list<SoundElement*> mSoundElements;
			std::list<SoundElement*>::iterator mGetIndex(sf::Sound *s);
		};

		//Old sound
		/*class SoundEngine
		{
		public:
			SoundEngine(Game *parent);

			void playSound(sf::Sound *s);
			void pauseSound(sf::Sound *s);
			void stopSound(sf::Sound *s);
			float getVolume(sf::Sound *s);
			void setVolume(sf::Sound *s, float x);
			int getStatus(sf::Sound *s);
			float getPosition(sf::Sound *s);
			void setPosition(sf::Sound *s, float x);
			void crossfade(sf::Sound *s1, float t, sf::Sound *s2, float v);

		private:
			Game *mParent;
		};*/
	}
}

#else
#error Sound.h: Wrong Version 0.1.7
#endif

#endif