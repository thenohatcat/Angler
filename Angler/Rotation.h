#ifndef INC_ROTATION_H
#define INC_ROTATION_H

#include "Node.h"

class Rotation
	: public Node
{
public:
	Rotation(float rotation);
	Rotation(Node *parent, float rotation);

	void updateRotation(float rot);

	virtual void draw(Game* context, Graphics* graphics, float time, float deltaTime);

private:
	float mRotation;
};

#endif