//Version: 0.1.9
//Author: Jakob Pipping
//Contributors:

#ifndef INC_UPDATEABLE_H
#define INC_UPDATEABLE_H

#ifdef ANGLER_0_1_9

#include "Game.h"

namespace Angler
{
	//Interface for "updateable" objects
	class Updateable
	{
	public:
		virtual void update(Game* context, float time, float deltaTime, bool changed = false) = 0;
	};
}

#else
#error Updateable.h: Wrong Version 0.1.9
#endif

#endif