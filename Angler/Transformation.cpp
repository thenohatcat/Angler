//Version: 0.1.9
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_9
#error Transformation.cpp: Wrong Version 0.1.9
#endif

#include "Transformation.h"

#include <SFML\OpenGL.hpp>
#include <glm/matrix.hpp>
#include <SFML\System\Vector2.hpp>

#include "HelpFunctions.h"

using namespace Angler::Nodes;
using namespace Angler::HelpFunctions;
using namespace Angler::HelpFunctions::Nodes;

Transformation::Transformation(unsigned long id)
	: Node(id)
{
	
}

Transformation::Transformation(unsigned long id, Node *parent)
	: Node(id, parent)
{

}

sf::Vector2f Transformation::transform(sf::Vector2f vec)
{
	sf::Vector2f v;
	transform(&vec, &v, 1);
	return v;
}

void Transformation::transform(Node *n)
{
	glLoadIdentity();

	std::vector<Node*> ansc = getAnscestors(n);
	std::vector<Transformation*> transf;

	Node *node = n;

	for (unsigned int i = 0; i < ansc.size(); i++)
	{
		if (isDerivedFrom<Transformation>(ansc.at(i)))
			transf.push_back((Transformation*)ansc.at(i));
	}

	for (std::vector<Transformation*>::const_iterator i = transf.end(); i != transf.begin();)
	{
		(*--i)->doTransform();
	}
}

void Transformation::transform(Node *n, sf::Vector2f *vIn, sf::Vector2f *vOut, int count)
{
	glPushMatrix();

	transform(n);

	GLfloat matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

	for (int i = 0; i < count; i++)
	{
		vOut[i] = Angler::HelpFunctions::Geometry::transform(matrix, vIn[i]);
	}

	glPopMatrix();
}

void Transformation::transform(Node *n, std::vector<sf::Vector2f> vIn, std::vector<sf::Vector2f> *vOut)
{
	sf::Vector2f *vInA = new sf::Vector2f[vIn.size()];
	sf::Vector2f *vOutA = new sf::Vector2f[vIn.size()];
	for (unsigned int i = 0; i < vIn.size(); i++)
	{
		vInA[i] = vIn.at(i);
	}
	transform(n, vInA, vOutA, vIn.size());
	for (unsigned int i = 0; i < vIn.size(); i++)
	{
		vOut->push_back(vOutA[i]);
	}
	delete vInA;
	delete vOutA;
}

void Transformation::transform(sf::Vector2f *vIn, sf::Vector2f *vOut, int count)
{
	transform(this, vIn, vOut, count);
}

void Transformation::transform(std::vector<sf::Vector2f> vIn, std::vector<sf::Vector2f> *vOut)
{
	transform(this, vIn, vOut);
}

void Transformation::draw(Angler::Game *context, Angler::Graphics::GraphicsEngine *graphics, float time, float deltaTime)
{
	if (mVisible)
	{
		glPushMatrix();

		//Does the transformation of the derived object
		doTransform();

		//Draws all children in the SAME graphics context (before glPopMatrix)
		mDrawChildren(context, graphics, time, deltaTime);

		glPopMatrix();
	}
}