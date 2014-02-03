//Version: 0.1.2
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_2
#error DrawNode.cpp: Wrong Version 0.1.2
#endif

#include "DrawNode.h"

using namespace Angler;
using namespace Angler::Nodes;

DrawNode::DrawNode(unsigned long id, Node *parent, int layer, sf::Texture *tx, float ox, float oy)
	: Node(id, parent), mTX(tx), mLayer(layer), mOX(ox), mOY(oy)
{

}

DrawNode::DrawNode(unsigned long id, Node *parent, int layer, sf::Texture *tx, sf::Vector2f origo)
	: Node(id, parent), mTX(tx), mLayer(layer), mOX(origo.x), mOY(origo.y)
{

}

DrawNode::DrawNode(unsigned long id, int layer, sf::Texture *tx, float ox, float oy)
	: Node(id), mTX(tx), mLayer(layer), mOX(ox), mOY(oy)
{

}

DrawNode::DrawNode(unsigned long id, int layer, sf::Texture *tx, sf::Vector2f origo)
	: Node(id), mTX(tx), mLayer(layer), mOX(origo.x), mOY(origo.y)
{

}

void DrawNode::draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime)
{
	graphics->draw(mLayer, mTX, mOX, mOY);

	mDrawChildren(context, graphics, time, deltaTime);
}