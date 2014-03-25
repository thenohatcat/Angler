//Version: 0.1.12
//Author: Jakob Pipping
//Contributors:

#ifndef INC_NODE_H
#define INC_NODE_H

#ifdef ANGLER_0_1_12

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

		virtual ~Node();

		//Adds a child to this node, and makes this node it's parent
		void addChild(Node* node);

		void orphanChild(Node* node);
		void removeChild(Node* node);

		void orphan();

		void clearChildren();

		//Not true virtual functions, as nodes shall be able to be implemented as
		//root nodes
		virtual void draw(Game *context, Angler::Graphics::GraphicsEngine *graphics, 
			float time, float deltaTime);

		virtual void endDraw(Game *context, Angler::Graphics::GraphicsEngine *graphics,
			float time, float deltaTime);

		virtual void update(Game *context, float time, float deltaTime, bool changed = false);

		Node *getParent();

		unsigned long getID();

		std::vector<Node*> getChildren();

		Node getIsolated();

		bool getChanged();

		void pause(bool paused);
		bool getPaused();

		void enable(bool enabled);
		bool getEnabled();

		void show(bool show);
		bool getVisible();

	protected:
		Node *mParent;

		virtual void mEnable(bool enabled);

		//Draws/updates all children in the vector
		void mDrawChildren(Game *context, Angler::Graphics::GraphicsEngine *graphics, float time, float deltaTime);
		void mEndDrawChildren(Game *context, Angler::Graphics::GraphicsEngine *graphics, float time, float deltaTime);
		void mUpdateChildren(Game *context, float time, float deltaTime);

		typedef std::vector<Node*> NodeVector;

		bool mChanged;
		
		bool mPaused;

		bool mEnabled;

		bool mVisible;

	private:
		NodeVector mChildren;

		unsigned long mID;
	};
}

#else
#error Node.h: Wrong Version 0.1.12
#endif

#endif