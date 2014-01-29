#include "Node.h"

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
		//Throw error
	}
}

void Node::clearChildren()
{
	mChildren.clear();
}

void Node::draw(Game* context, Graphics* graphics, float time, float deltaTime)
{
	mDrawChildren(context, graphics, time, deltaTime);
}

void Node::update(Game* context, float time, float deltaTime)
{
	mUpdateChildren(context, time, deltaTime);
}

void Node::mDrawChildren(Game* context, Graphics* graphics, float time, float deltaTime)
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