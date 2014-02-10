//Version: 0.1.4
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_4
#error DrawNode.cpp: Wrong Version 0.1.4
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

void DrawNode::setOrigin(float x, float y)
{
	mOX = x;
	mOY = y;
}

void DrawNode::setOrigin(sf::Vector2f origin)
{
	setOrigin(origin.x, origin.y);
}

sf::Vector2f DrawNode::getOrigin()
{
	return sf::Vector2f(getOriginX(), getOriginY());
}

float DrawNode::getOriginX()
{
	return mOX;
}

float DrawNode::getOriginY()
{
	return mOY;
}