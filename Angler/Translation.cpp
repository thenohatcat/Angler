#include "Translation.h"

#include <glut.h>

Translation::Translation(Node *parent, float x, float y)
	: Node(parent), mX(x), mY(y)
{

}

Translation::Translation(float x, float y)
	: Node(), mX(x), mY(y)
{

}

void Translation::updateTranslation(float x, float y)
{
	mX = x;
	mY = y;
}

void Translation::draw(Game* context, Graphics* graphics, float time, float deltaTime)
{
	glPushMatrix();

	glTranslatef(mX, mY, 0);

	mDrawChildren(context, graphics, time, deltaTime);

	glPopMatrix();
}