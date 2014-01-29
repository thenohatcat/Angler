//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

//Changelog:
//Added DrawNode(Node*, int, sf::Texture*, sf::Vector2f)
//Added DrawNode(int, sf::Texture*, sf::Vector2f)

#ifndef INC_DRAWNODE_H
#define INC_DRAWNODE_H

#ifdef ANGLER_0_1_1

#include "../Angler_0_1_0/Node.h"
#include "../Angler_0_1_0/Graphics.h"
#include <SFML\Graphics\Texture.hpp>

class DrawNode
	: public Node
{
public:
	DrawNode(Node *parent, int layer, sf::Texture *tx, float ox = 0, float oy = 0);
	DrawNode(Node *parent, int layer, sf::Texture *tx, sf::Vector2f origo);

	DrawNode(int layer, sf::Texture *tx, float ox = 0, float oy = 0);
	DrawNode(int layer, sf::Texture *tx, sf::Vector2f origo);

	void draw(Game* context, Graphics* graphics, float time, float deltaTime);

private:
	int mLayer;
	sf::Texture *mTX;
	float mOX, mOY;
};

#else
#error DrawNode.h: Wrong Version 0.1.1
#endif

#endif