//Version: 0.1.2
//Author: Jakob Pipping
//Contributors:

//Changelog:
// - removed	Node()
// - removed	Node(Node*)
// + added		Node(unsigned long)
// + added		Node(unsigned long, Node*)
// + added		unsigned long getID();
// + added		unsigned long mID;

#ifndef INC_NODE_H
#define INC_NODE_H

#ifdef ANGLER_0_1_2

#include <vector>

#include "Game.h"
#include "Graphics.h"

#include "Drawable.h"
#include "Updateable.h"

namespace Angler
{
	class Node
		: public Drawable, public Updateable
	{
	public:
		Node(unsigned long id);

		Node(unsigned long id, Node *parent);

		//Adds a child to this node, and makes this node it's parent
		void addChild(Node* node);

		void clearChildren();

		//Not true virtual functions, as nodes shall be able to be implemented as
		//root nodes
		virtual void draw(Game *context, Angler::Graphics::GraphicsEngine *graphics, 
			float time, float deltaTime);

		virtual void update(Game *context, float time, float deltaTime);

		Node *getParent();

		unsigned long getID();

	protected:
		Node *mParent;

		//Draws/updates all children in the vector
		void mDrawChildren(Game *context, Angler::Graphics::GraphicsEngine *graphics, float time, float deltaTime);
		void mUpdateChildren(Game *context, float time, float deltaTime);

		typedef std::vector<Node*> NodeVector;

	private:
		NodeVector mChildren;

		unsigned long mID;
	};
}

#else
#error Node.h: Wrong Version 0.1.2
#endif

#endif