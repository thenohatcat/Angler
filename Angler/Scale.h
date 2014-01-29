#ifndef INC_SCALE_H
#define INC_SCALE_H

#include "Node.h"

class Scale
	: public Node
{
public:
	Scale(float scaleX, float scaleY);
	Scale(Node *parent, float scaleX, float scaleY);

	void updateScale(float scaleX, float scaleY);

	virtual void draw(Game* context, Graphics* graphics, float time, float deltaTime);

private:
	float mScaleX, mScaleY;
};


#endif