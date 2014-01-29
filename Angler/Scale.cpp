//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_1
#error Scale.cpp: Wrong Version 0.1.1
#endif

#include "Scale.h"

#include <glut.h>

Scale::Scale(float scaleX, float scaleY)
	: Transformation(), mScaleX(scaleX), mScaleY(scaleY)
{

}

Scale::Scale(sf::Vector2f s)
	: Transformation(), mScaleX(s.x), mScaleY(s.y)
{

}

Scale::Scale(Node *parent, float scaleX, float scaleY)
	: Transformation(parent), mScaleX(scaleX), mScaleY(scaleY)
{

}

Scale::Scale(Node *parent, sf::Vector2f s)
	: Transformation(parent), mScaleX(s.x), mScaleY(s.y)
{

}

void Scale::setScale(float scaleX, float scaleY)
{
	mScaleX = scaleX;
	mScaleY = scaleX;
}

void Scale::setScale(sf::Vector2f s)
{
	setScale(s.x, s.y);
}

void Scale::scale(float scaleX, float scaleY)
{
	mScaleX *= scaleX;
	mScaleY *= scaleY;
}

void Scale::scale(sf::Vector2f s)
{
	scale(s.x, s.y);
}

sf::Vector2f Scale::getScale()
{
	return sf::Vector2f(mScaleX, mScaleY);
}

float Scale::getScaleX()
{
	return mScaleX;
}

float Scale::getScaleY()
{
	return mScaleY;
}

void Scale::draw(Game* context, Graphics* graphics, float time, float deltaTime)
{
	glPushMatrix();

	doTransform();
	
	mDrawChildren(context, graphics, time, deltaTime);

	glPopMatrix();
}

void Scale::doTransform()
{
	glScalef(mScaleX, mScaleY, 0);
}