//Version: 0.1.6
//Author: Jakob Pipping
//Contributors:

//Changelog:
//Updateable:
// - removed	virtual void update(Game*, float, float);
// + added		virtual void update(Game*, float, float, bool);

#ifndef INC_UPDATEABLE_H
#define INC_UPDATEABLE_H

#ifdef ANGLER_0_1_6

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
#error Updateable.h: Wrong Version 0.1.6
#endif

#endif