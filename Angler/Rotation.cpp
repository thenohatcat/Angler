#include "Rotation.h"

#include <glut.h>

Rotation::Rotation(Node *parent, float rotation)
	: Node(parent), mRotation(rotation)
{

}

Rotation::Rotation(float rotation)
	: Node(), mRotation(rotation)
{

}

void Rotation::updateRotation(float rotation)
{
	mRotation = rotation;
}

void Rotation::draw(Game* context, Graphics* graphics, float time, float deltaTime)
{
	glPushMatrix();

	glRotatef(mRotation, 0, 0, 1);

	mDrawChildren(context, graphics, time, deltaTime);

	glPopMatrix();
}