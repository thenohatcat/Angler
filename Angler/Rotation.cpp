//Version: 0.1.3
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_3
#error Rotation.cpp: Wrong Version 0.1.3
#endif

#include "Rotation.h"

#include <glut.h>

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
}

void Rotation::rotate(float rotation)
{
	//Modulo with 360, to keep the rotation within [0, 360)
	mRotation = fmod(mRotation + rotation, 360);
}

float Rotation::getRotation()
{
	//Modulo around 360, to keep the rotation within [0, 360)
	return fmod(mRotation, 360);
}

void Rotation::doTransform()
{
	//Normal opengl rotation
	glRotatef(mRotation, 0, 0, 1);
}