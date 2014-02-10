//Version: 0.1.5
//Author: Oskar Engblad
//Contributors: Jakob Pipping

#ifndef INC_SOUND_H
#define INC_SOUND_H

#ifdef ANGLER_0_1_5

namespace Angler
{
	class Game;

	namespace Sound
	{
		class SoundEngine
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
		};
	}
}

#else
#error Sound.h: Wrong Version 0.1.5
#endif

#endif