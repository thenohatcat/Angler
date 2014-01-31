//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef INC_DRAWABLE_H
#define INC_DRAWABLE_H

#ifdef ANGLER_0_1_1

namespace Angler
{
	class Game;

	namespace Graphics
	{
		class GraphicsEngine;
	}

	class Drawable
	{
	public:
		virtual void draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime) = 0;
	};
}

#else
#error DrawNode.h: Wrong Version 0.1.1
#endif

#endif