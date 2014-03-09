//Version: 0.1.9
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_9
#error Rotation.cpp: Wrong Version 0.1.9
#endif

#include "Rotation.h"

#include <SFML\OpenGL.hpp>

using namespace Angler;
using namespace Angler::Nodes;

Rotation::Rotation(unsigned long id, Node *parent, float rotation)
	: Transformation(id, parent), mRotation(rotation)
{

}

Rotation::Rotation(unsigned long id, float rotation)
	: Transformation(id), mRotation(rotation)
{

}

void Rotation::setRotation(float rotation)
{
	//Modulo with 360, to keep the rotation within [0, 360)
	mRotation = fmod(rotation, 360);
	mChanged = true;
}

void Rotation::rotate(float rotation)
{
	//Modulo with 360, to keep the rotation within [0, 360)
	mRotation = fmod(mRotation + rotation, 360);
	mChanged = true;
}

float Rotation::getRotation()
{
	//Modulo around 360, to keep the rotation within [0, 360)
	return mRotation;
}

void Rotation::doTransform()
{
	//Normal opengl rotation
	glRotatef(mRotation, 0, 0, 1);
}

void Rotation::doInverseTransform()
{
	//Normal opengl rotation
	glRotatef(-mRotation, 0, 0, 1);
}