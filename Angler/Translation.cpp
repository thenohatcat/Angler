//Version: 0.1.6
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_6
#error Translation.cpp: Wrong Version 0.1.6
#endif

#include "Translation.h"

#include <SFML\OpenGL.hpp>

using namespace Angler;
using namespace Angler::Nodes;

Translation::Translation(unsigned long id, Node *parent, float x, float y)
	: Transformation(id, parent), mX(x), mY(y)
{
	
}

Translation::Translation(unsigned long id, Node *parent, sf::Vector2f translation)
	: Transformation(id, parent), mX(translation.x), mY(translation.y)
{

}

Translation::Translation(unsigned long id, float x, float y)
	: Transformation(id), mX(x), mY(y)
{

}

Translation::Translation(unsigned long id, sf::Vector2f translation)
	: Transformation(id), mX(translation.x), mY(translation.y)
{
	
}

void Translation::setTranslation(float x, float y)
{
	mX = x;
	mY = y;
	mChanged = true;
}

void Translation::setTranslation(sf::Vector2f translation)
{
	setTranslation(translation.x, translation.y);
}

void Translation::translate(float x, float y)
{
	mX += x;
	mY += y;
	mChanged = true;
}

void Translation::translate(sf::Vector2f translation)
{
	translate(translation.x, translation.y);
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

void Translation::doTransform()
{
	//Normal opengl transformation
	glTranslatef(mX, mY, 0);
}