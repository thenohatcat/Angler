//Version: 0.1.9
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_9
#error Node.cpp: Wrong Version 0.1.9
#endif

#include "Node.h"

#include "Exceptions.h"

using namespace Angler;
using namespace Angler::Exceptions;

Node::Node(unsigned long id)
	: mParent(0), mChildren(), mID(id), mChanged(true)
{

}

Node::Node(unsigned long id, Node *parent)
	: mParent(0), mChildren(), mID(id), mChanged(true)
{
	parent->addChild(this);
}

Node::~Node()
{
	clearChildren();
	orphan();
}

void Node::orphanChild(Node* node)
{
	for (NodeVector::const_iterator i = mChildren.begin(); i != mChildren.end(); )
	{
		if ((*i) == node)
		{
			Node *n = *i;
			i = mChildren.erase(i);
			n->mParent = nullptr;
		}
		else
		{
			i++;
		}
	}
}

void Node::removeChild(Node* node)
{
	for (NodeVector::const_iterator i = mChildren.begin(); i != mChildren.end(); )
	{
		if ((*i) == node)
		{
			Node *n = *i;
			i = mChildren.erase(i);
			delete n;
			//n->mParent = nullptr;
		}
		else
		{
			i++;
		}
	}
}

void Node::orphan()
{
	if (mParent != nullptr)
		mParent->orphanChild(this);
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
	for (NodeVector::iterator i = mChildren.begin(); i != mChildren.end();)
	{
		Node *n = *i;
		i = mChildren.erase(i);
		delete n;
		//n->mParent = nullptr;
	}
}

void Node::draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime)
{
	mDrawChildren(context, graphics, time, deltaTime);
}

void Node::update(Game* context, float time, float deltaTime, bool changed)
{
	if (!mPaused)
	{
		mChanged |= changed;

		mUpdateChildren(context, time, deltaTime);
	}
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
		(*i)->update(context, time, deltaTime, mChanged);
	}

	mChanged = false;
}

Node* Node::getParent()
{
	return mParent;
}

unsigned long Node::getID()
{
	return mID;
}

bool Node::getChanged()
{
	return mChanged;
}

Node Node::getIsolated()
{
	//Isolates this node to be able to run it without the hierarchy
	Node n(*this);
	n.mParent = 0;
	return n;
}

std::vector<Node*> Node::getChildren()
{
	return std::vector<Node*>(mChildren);
}

void Node::pause(bool paused)
{
	mPaused = paused;
}