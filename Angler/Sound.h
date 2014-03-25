//Version: 0.1.11
//Author: Jakob Pipping
//Contributors:

#ifndef INC_SOUND_H
#define INC_SOUND_H

#ifdef ANGLER_0_1_11

#include <SFML\Audio\Sound.hpp>
#include <list>

namespace Angler
{
	class Game;

	namespace Sound	
	{
		class SoundState;
		class SoundEngine;

		class SoundElement
		{
			friend class SoundState;
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

		class SoundState final
		{
			friend class SoundEngine;

		public:
			SoundState(unsigned long id, float volume, float sart, float end);

			unsigned long getID();

			void update(SoundElement* element);

		private:
			unsigned long mID;

			float mStart, mEnd;

			float mVolume;
		};

		class SoundEngine final
		{
		public:
			SoundEngine(Game *parent);

			bool playSound(sf::Sound *s, bool hard = true, 
				float start = -1, float end = -1, bool loop = false);
			bool playSound(sf::Sound *s, bool hard, unsigned long stateID, bool loop = false);

			void stopSound(sf::Sound *s);
			void pauseSound(sf::Sound *s);
			float getVolume(sf::Sound *s);
			void setVolume(sf::Sound *s, float x);
			int getStatus(sf::Sound *s);
			float getPosition(sf::Sound *s);
			void setPosition(sf::Sound *s, float x);
			void updateState(sf::Sound *s, unsigned long stateID);

			void loadStates(std::string file);
			//void crossfade(sf::Sound *s1, float t, sf::Sound *s2, float v);

			void update(float time, float deltaTime);

			void addSoundState(unsigned long id, float volume, float start, float end);

		private:
			Game *mParent;
			std::list<SoundElement*> mSoundElements;
			std::list<SoundElement*>::iterator mGetElementIndex(sf::Sound *s);
			std::list<SoundState*> mSoundStates;
			std::list<SoundState*>::iterator mGetStateIndex(unsigned long id);
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
#error Sound.h: Wrong Version 0.1.11
#endif

#endif