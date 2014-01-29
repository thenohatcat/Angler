#ifndef INC_TRANSLATION_H
#define INC_TRANLSATION_H

#include "Node.h"

class Translation
	: public Node
{
public:
	Translation(float x, float y);
	Translation(Node *parent, float x, float y);

	void updateTranslation(float x, float y);

	virtual void draw(Game* context, Graphics* graphics, float time, float deltaTime);

private:
	float mX, mY;
};

#endif