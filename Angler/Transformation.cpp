#include "Transformation.h"

#include <glut.h>
#include <glm/matrix.hpp>
#include <SFML\System\Vector2.hpp>

#include "HelpFunctions.h"

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

void Transformation::transform(sf::Vector2f *vIn, sf::Vector2f *vOut, int count)
{
	glPushMatrix();

	glLoadIdentity();

	std::vector<Transformation*> transf;

	Node *node = this;

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

	GLdouble matrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);

	for (int i = 0; i < count; i++)
	{
		vOut[i] = Angler::HelpFunctions::transform(matrix, vIn[i]);
	}

	glPopMatrix();
}

void Transformation::transform(std::vector<sf::Vector2f> vIn, std::vector<sf::Vector2f> *vOut)
{
	sf::Vector2f *vInA = new sf::Vector2f[vIn.size()];
	sf::Vector2f *vOutA = new sf::Vector2f[vIn.size()];
	for (int i = 0; i < vIn.size(); i++)
	{
		vInA[i] = vIn.at(i);
	}
	transform(vInA, vOutA, vIn.size());
	for (int i = 0; i < vIn.size(); i++)
	{
		vOut->push_back(vOutA[i]);
	}
}