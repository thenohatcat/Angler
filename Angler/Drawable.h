#ifndef INC_DRAWABLE_H
#define INC_DRAWABLE_H

class Game;
class Graphics;

class Drawable
{
public:
	virtual void draw(Game* context, Graphics* graphics, float time, float deltaTime) = 0;
};

#endif