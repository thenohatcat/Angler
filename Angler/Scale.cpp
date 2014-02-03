//Version: 0.1.2
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_2
#error Scale.cpp: Wrong Version 0.1.2
#endif

#include "Scale.h"

#include <glut.h>

using namespace Angler;
using namespace Angler::Nodes;

Scale::Scale(unsigned long id, float scaleX, float scaleY)
	: Transformation(id), mScaleX(scaleX), mScaleY(scaleY)
{

}

Scale::Scale(unsigned long id, sf::Vector2f s)
	: Transformation(id), mScaleX(s.x), mScaleY(s.y)
{

}

Scale::Scale(unsigned long id, Node *parent, float scaleX, float scaleY)
	: Transformation(id, parent), mScaleX(scaleX), mScaleY(scaleY)
{

}

Scale::Scale(unsigned long id, Node *parent, sf::Vector2f s)
	: Transformation(id, parent), mScaleX(s.x), mScaleY(s.y)
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

void Scale::doTransform()
{
	//Normal opengl scale
	glScalef(mScaleX, mScaleY, 0);
}