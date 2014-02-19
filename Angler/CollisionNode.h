//Version: 0.1.8
//Author: Jakob Pipping
//Contributors:

#ifndef INC_COLLISIONNODE_H
#define INC_COLLISIONNODE_H

#ifdef ANGLER_0_1_8

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
			CollisionNode(unsigned long id, const std::vector<sf::Vector2f> &pts, int type);
			CollisionNode(unsigned long id, Node *parent, const std::vector<sf::Vector2f> &pts, int type);

			//Returns:
			//0 if the nodes aren't colliding
			//1 if the nodes are colliding
			//2 if the nodes aren't colliding, but their bounding-boxes intersect
			int isColliding(CollisionNode *node);

			//Returns the points of the collision shape
			std::vector<sf::Vector2f> getPoints();

			std::vector<sf::Vector2f> getTransformedPoints();

			sf::Vector2f getBoundingUL(), getBoundingLR();

			int getType();

			//Draws the bounding box of the shape
			virtual void draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, 
				float time, float deltaTime);
			
			virtual void update(Game* context, float time, float deltaTime, bool changed);
		private:
			std::vector<sf::Vector2f> mPoints;
			std::vector<sf::Vector2f> mTransformedPoints;
			sf::Vector2f mUL, mLR;
			std::vector<sf::Vector2f> mBounding;

			//type 0: Collides with everything
			//type 1: Only collides with type 0
			unsigned short mType;

			unsigned int mRegion;
		};
	}
}

#else
#error CollisionNode.h: Wrong Version 0.1.8
#endif

#endif