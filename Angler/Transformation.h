//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef INC_TRANSFORMATION_H
#define INC_TRANSFORMATION_H

#ifdef ANGLER_0_1_1

#include "Node.h"

#include <SFML\System\Vector2.hpp>

class Transformation
	: public Node
{
public:
	Transformation();
	Transformation(Node *parent);

	sf::Vector2f transform(sf::Vector2f v);

	void transform(sf::Vector2f *vIn, sf::Vector2f *vOut, int count);
	void transform(std::vector<sf::Vector2f> vIn, std::vector<sf::Vector2f> *vOut);

	virtual void doTransform() = 0;
};

#else
#error Transformation.h: Wrong Version 0.1.1
#endif

#endif