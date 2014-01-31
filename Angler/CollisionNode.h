//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef INC_COLLISIONNODE_H
#define INC_COLLISIONNODE_H

#ifdef ANGLER_0_1_1

#include "Node.h"
#include <SFML\System\Vector2.hpp>

namespace Angler
{
	namespace Nodes
	{
		class CollisionNode
			: public Angler::Node
		{
		public:
			CollisionNode(const std::vector<sf::Vector2f> &pts);
			CollisionNode(Node *parent, const std::vector<sf::Vector2f> &pts);

			int isColliding(CollisionNode *node);
			std::vector<sf::Vector2f> getPoints();

			virtual void draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime);
		private:
			std::vector<sf::Vector2f> mPoints;
		};
	}
}

#else
#error CollisionNode.h: Wrong Version 0.1.1
#endif

#endif