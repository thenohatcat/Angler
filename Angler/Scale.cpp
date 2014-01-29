#include "Scale.h"
#include <glut.h>

Scale::Scale(float scaleX, float scaleY)
	: Node(), mScaleX(scaleX), mScaleY(scaleY)
{

}

Scale::Scale(Node *parent, float scaleX, float scaleY)
	: Node(parent), mScaleX(scaleX), mScaleY(scaleY)
{

}

void Scale::updateScale(float scaleX, float scaleY)
{
	mScaleX = scaleX;
	mScaleY = scaleX;
}

void Scale::draw(Game* context, Graphics* graphics, float time, float deltaTime)
{
	glPushMatrix();

	glScalef(mScaleX, mScaleY, 0);
	
	mDrawChildren(context, graphics, time, deltaTime);

	glPopMatrix();
}