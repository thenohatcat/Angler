//Version: 0.1.4
//Author: 
//Contributors: Jakob Pipping

#ifndef INC_SOUND_H
#define INC_SOUND_H

#ifdef ANGLER_0_1_4

namespace Angler
{
	class Game;

	namespace Sound
	{
		class SoundEngine
		{
		public:
			SoundEngine(Game *parent);

			playSound();
			stopSound();
			getStatus();
			getPosition();
			setPosition();

		private:
			Game *mParent;
		};
	}
}

#else
#error Sound.h: Wrong Version 0.1.4
#endif

#endif