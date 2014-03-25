//Version: 0.1.11
//Author: Jakob Pipping
//Contributors:

#ifndef INC_COLLISIONNODE_H
#define INC_COLLISIONNODE_H

#ifdef ANGLER_0_1_11

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
			//Creates a new collision node
			CollisionNode(unsigned long id, const std::vector<sf::Vector2f> &pts, int type);

			//Creates a new collision node with a parent
			CollisionNode(unsigned long id, Node *parent, const std::vector<sf::Vector2f> &pts, int type);

			virtual ~CollisionNode();

			//Returns:
			//0 if the nodes aren't colliding
			//1 if the nodes are colliding
			//2 if the nodes aren't colliding, but their bounding-boxes intersect
			int isColliding(CollisionNode *node);

			//Returns the points of the collision shape
			std::vector<sf::Vector2f> getPoints();

			//Returns the transformed collision shape
			std::vector<sf::Vector2f> getTransformedPoints();

			//Returns the bounding shape
			sf::Vector2f getBoundingUL(), getBoundingLR();

			//Returns the type of the collison node
			int getType();

			void setCollision(const std::vector<sf::Vector2f> &pts);

			//Draws the bounding box of the shape
			virtual void draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, 
				float time, float deltaTime);
			
			virtual void update(Game* context, float time, float deltaTime, bool changed);
		private:
			//The points of the collision shape, untransformed
			std::vector<sf::Vector2f> mPoints;
			//The transformed points of the collison shape
			std::vector<sf::Vector2f> mTransformedPoints;
			//Bounding points
			sf::Vector2f mUL, mLR;
			std::vector<sf::Vector2f> mBounding;

			//type 0: Only Collides with type 0 and type 1
			//type 1: Only collides with type 0
			//type 2: Only collides with other type 2 and type 3
			//type 3: only collides with type 2
			unsigned short mType;
		};
	}
}

#else
#error CollisionNode.h: Wrong Version 0.1.11
#endif

#endif