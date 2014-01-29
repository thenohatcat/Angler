#ifndef INC_NODE_H
#define INC_NODE_H

#include <vector>

#include "Drawable.h"
#include "Updateable.h"

class Game;
class Graphics;

class Node
	: public Drawable, public Updateable
{
public:
	Node();

	void addChild(Node* node);

	void clearChildren();

	virtual void draw(Game *context, Graphics *graphics, float time, float deltaTime);

	virtual void update(Game *context, float time, float deltaTime);

protected:
	Node(Node *parent);

	Node *mParent;

	void mDrawChildren(Game *context, Graphics *graphics, float time, float deltaTime);
	void mUpdateChildren(Game *context, float time, float deltaTime);

	typedef std::vector<Node*> NodeVector;

private:
	NodeVector mChildren;
};

#endif