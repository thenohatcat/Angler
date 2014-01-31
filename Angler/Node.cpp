//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_1
#error Node.cpp: Wrong Version 0.1.1
#endif

#include "Node.h"

#include "Exceptions.h"

using namespace Angler;
using namespace Angler::Exceptions;

Node::Node()
	: mParent(0), mChildren()
{

}

Node::Node(Node *parent)
	: mParent(0), mChildren()
{
	parent->addChild(this);
}

void Node::addChild(Node* node)
{
	if (node->mParent == 0)
	{
		node->mParent = this;
		mChildren.push_back(node);
	}
	else
	{
		//Thrown if this node already has a parent
		throw node_already_has_parent_exception();
	}
}

void Node::clearChildren()
{
	mChildren.clear();
}

void Node::draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime)
{
	mDrawChildren(context, graphics, time, deltaTime);
}

void Node::update(Game* context, float time, float deltaTime)
{
	mUpdateChildren(context, time, deltaTime);
}

void Node::mDrawChildren(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime)
{
	for (NodeVector::iterator i = mChildren.begin(); i != mChildren.end(); i++)
	{
		(*i)->draw(context, graphics, time, deltaTime);
	}
}

void Node::mUpdateChildren(Game* context, float time, float deltaTime)
{
	for (NodeVector::iterator i = mChildren.begin(); i != mChildren.end(); i++)
	{
		(*i)->update(context, time, deltaTime);
	}
}

Node* Node::getParent()
{
	return mParent;
}