//Version: 0.1.4
//Author: Marcus Persson
//Contributors: Jakob Pipping

#ifndef INC_MECHANICS_H
#define INC_MECHANICS_H

#ifdef ANGLER_0_1_4

namespace Angler
{
	class Game;

	class Node;

	namespace Mechanics
	{
		class MechanicsEngine
		{
		public:
			MechanicsEngine(Angler::Game *game);
			~MechanicsEngine();
			void doCollide(Angler::Node *node);
		private:
			Angler::Game *mParent;
		};
	}
}

#else
#error Mechanics.h: Wrong Version 0.1.4
#endif

#endif