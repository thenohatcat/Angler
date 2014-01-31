//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef INC_UPDATEABLE_H
#define INC_UPDATEABLE_H

#ifdef ANGLER_0_1_1

namespace Angler
{
	class Game;

	class Updateable
	{
	public:
		virtual void update(Game* context, float time, float deltaTime) = 0;
	};
}

#else
#error Updateable.h: Wrong Version 0.1.1
#endif

#endif