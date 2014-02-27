//Version: 0.1.9
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_9
#error DrawNode.cpp: Wrong Version 0.1.9
#endif

#include "DrawNode.h"

using namespace Angler;
using namespace Angler::Nodes;

DrawNode::DrawNode(unsigned long id, Node *parent, int layer, float ox, float oy)
	: Node(id, parent), mLayer(layer), mOX(ox), mOY(oy)
{

}

DrawNode::DrawNode(unsigned long id, Node *parent, int layer, sf::Vector2f origo)
	: Node(id, parent), mLayer(layer), mOX(origo.x), mOY(origo.y)
{

}

DrawNode::DrawNode(unsigned long id, int layer, float ox, float oy)
	: Node(id), mLayer(layer), mOX(ox), mOY(oy)
{

}

DrawNode::DrawNode(unsigned long id, int layer, sf::Vector2f origo)
	: Node(id), mLayer(layer), mOX(origo.x), mOY(origo.y)
{

}

DrawNode::~DrawNode()
{
	Node::~Node();
}

void DrawNode::draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime)
{
	graphics->draw(mLayer, mOX, mOY);

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