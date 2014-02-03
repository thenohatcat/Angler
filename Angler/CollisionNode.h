//Version: 0.1.2
//Author: Jakob Pipping
//Contributors:

//Changelog:
// - removed		CollisionNode(const std::vector<sf::Vector2f>&)
// - removed		CollisionNode(Node*, const std::vector<sf::Vector2f>&)
// + added		CollisionNode(unsigned long, const std::vector<sf::Vector2f>&)
// + added		CollisionNode(unsigned long, Node*, const std::vector<sf::Vector2f>&)

#ifndef INC_COLLISIONNODE_H
#define INC_COLLISIONNODE_H

#ifdef ANGLER_0_1_2

#include "Node.h"
#include <SFML\System\Vector2.hpp>

namespace Angler
{
	namespace Nodes
	{
		//A node used to keep collision data for an object, 
		//used to align the collision data with the transformation of the related object
		class CollisionNode
			: public Angler::Node
		{
		public:
			//Standard Node constructors, with a vector of points
			CollisionNode(unsigned long id, const std::vector<sf::Vector2f> &pts);
			CollisionNode(unsigned long id, Node *parent, const std::vector<sf::Vector2f> &pts);

			//Returns:
			//0 if the nodes aren't colliding
			//1 if the nodes are colliding
			//2 if the nodes aren't colliding, but their bounding-boxes intersect
			int isColliding(CollisionNode *node);

			//Returns the points of the collision shape
			std::vector<sf::Vector2f> getPoints();

			//Draws the bounding box of the shape
			//todo: Add functionality to deactivate
			virtual void draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, 
				float time, float deltaTime);
		private:
			std::vector<sf::Vector2f> mPoints;
		};
	}
}

#else
#error CollisionNode.h: Wrong Version 0.1.2
#endif

#endif