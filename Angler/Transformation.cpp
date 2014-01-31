//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_1
#error Transformation.cpp: Wrong Version 0.1.1
#endif

#include "Transformation.h"

#include <glut.h>
#include <glm/matrix.hpp>
#include <SFML\System\Vector2.hpp>

#include "HelpFunctions.h"

using namespace Angler::Nodes;

Transformation::Transformation()
	: Node()
{
	
}

Transformation::Transformation(Node *parent)
	: Node(parent)
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

	std::vector<Transformation*> transf;

	Node *node = n;

	while (node->getParent() != nullptr)
	{
		if (Angler::HelpFunctions::isDerivedFrom<Transformation>(node))
			transf.push_back((Transformation*)node);

		node = node->getParent();
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

	GLdouble matrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);

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
	for (int i = 0; i < vIn.size(); i++)
	{
		vInA[i] = vIn.at(i);
	}
	transform(n, vInA, vOutA, vIn.size());
	for (int i = 0; i < vIn.size(); i++)
	{
		vOut->push_back(vOutA[i]);
	}
}

void Transformation::transform(sf::Vector2f *vIn, sf::Vector2f *vOut, int count)
{
	transform(this, vIn, vOut, count);
}

void Transformation::transform(std::vector<sf::Vector2f> vIn, std::vector<sf::Vector2f> *vOut)
{
	transform(this, vIn, vOut);
}