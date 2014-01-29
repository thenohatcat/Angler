//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef INC_DRAWABLE_H
#define INC_DRAWABLE_H

#ifdef ANGLER_0_1_1

class Game;
class Graphics;

class Drawable
{
public:
	virtual void draw(Game* context, Graphics* graphics, float time, float deltaTime) = 0;
};

#else
#error DrawNode.h: Wrong Version 0.1.1
#endif

#endif