//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_1
#error DrawNode.cpp: Wrong Version 0.1.1
#endif

#include "DrawNode.h"

DrawNode::DrawNode(Node *parent, int layer, sf::Texture *tx, float ox, float oy)
	: Node(parent), mTX(tx), mLayer(layer), mOX(ox), mOY(oy)
{

}

DrawNode::DrawNode(Node *parent, int layer, sf::Texture *tx, sf::Vector2f origo)
	: Node(parent), mTX(tx), mLayer(layer), mOX(origo.x), mOY(origo.y)
{

}

DrawNode::DrawNode(int layer, sf::Texture *tx, float ox, float oy)
	: Node(), mTX(tx), mLayer(layer), mOX(ox), mOY(oy)
{

}

DrawNode::DrawNode(int layer, sf::Texture *tx, sf::Vector2f origo)
	: Node(), mTX(tx), mLayer(layer), mOX(origo.x), mOY(origo.y)
{

}

void DrawNode::draw(Game* context, Graphics* graphics, float time, float deltaTime)
{
	graphics->draw(mLayer, mTX, mOX, mOY);

	Node::draw(context, graphics, time, deltaTime);
}