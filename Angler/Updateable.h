#ifndef INC_UPDATEABLE_H
#define INC_UPDATEABLE_H

class Game;

class Updateable
{
public:
	virtual void update(Game* context, float time, float deltaTime) = 0;
};

#endif