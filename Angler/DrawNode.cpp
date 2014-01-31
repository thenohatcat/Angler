//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_1
#error DrawNode.cpp: Wrong Version 0.1.1
#endif

#include "DrawNode.h"

using namespace Angler;
using namespace Angler::Nodes;

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

void DrawNode::draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime)
{
	graphics->draw(mLayer, mTX, mOX, mOY);

	mDrawChildren(context, graphics, time, deltaTime);
}