//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

//Changelog:
//+ added		Node* getParent()

#ifndef INC_NODE_H
#define INC_NODE_H

#ifdef ANGLER_0_1_1

#include <vector>

#include "Drawable.h"
#include "Updateable.h"

namespace Angler
{
	class Game;

	namespace Graphics
	{
		class GraphicsEngine;
	}

	class Node
		: public Drawable, public Updateable
	{
	public:
		Node();

		void addChild(Node* node);

		void clearChildren();

		virtual void draw(Game *context, Angler::Graphics::GraphicsEngine *graphics, float time, float deltaTime);

		virtual void update(Game *context, float time, float deltaTime);

		Node *getParent();

	protected:
		Node(Node *parent);

		Node *mParent;

		void mDrawChildren(Game *context, Angler::Graphics::GraphicsEngine *graphics, float time, float deltaTime);
		void mUpdateChildren(Game *context, float time, float deltaTime);

		typedef std::vector<Node*> NodeVector;

	private:
		NodeVector mChildren;
	};
}

#else
#error Node.h: Wrong Version 0.1.1
#endif

#endif