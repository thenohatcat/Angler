//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_1
#error Translation.cpp: Wrong Version 0.1.1
#endif

#include "Translation.h"

#include <glut.h>

Translation::Translation(Node *parent, float x, float y)
	: Transformation(parent), mX(x), mY(y)
{

}

Translation::Translation(Node *parent, sf::Vector2f translation)
	: Transformation(parent), mX(translation.x), mY(translation.y)
{

}

Translation::Translation(float x, float y)
	: Transformation(), mX(x), mY(y)
{

}

Translation::Translation(sf::Vector2f translation)
	: Transformation(), mX(translation.x), mY(translation.y)
{

}

void Translation::setTranslation(float x, float y)
{
	mX = x;
	mY = y;
}

void Translation::setTranslation(sf::Vector2f translation)
{
	mX = translation.x;
	mY = translation.y;
}

void Translation::translate(float x, float y)
{
	mX += x;
	mY += y;
}

void Translation::translate(sf::Vector2f translation)
{
	mX += translation.x;
	mY += translation.y;
}

sf::Vector2f Translation::getTranslation()
{
	return sf::Vector2f(mX, mY);
}

float Translation::getTranslationX()
{
	return mX;
}

float Translation::getTranslationY()
{
	return mY;
}

void Translation::draw(Game* context, Graphics* graphics, float time, float deltaTime)
{
	glPushMatrix();

	doTransform();

	mDrawChildren(context, graphics, time, deltaTime);

	glPopMatrix();
}

void Translation::doTransform()
{
	glTranslatef(mX, mY, 0);
}