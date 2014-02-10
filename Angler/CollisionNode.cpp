//Version: 0.1.5
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_5
#error CollisionNode.cpp: Wrong Version 0.1.5
#endif

#include "CollisionNode.h"
#include "Transformation.h"
#include <glm\geometric.hpp>
#include <glm\gtx\intersect.hpp>

#include <glut.h>

#include "HelpFunctions.h"

using namespace Angler;
using namespace Angler::HelpFunctions::Geometry;
using namespace Angler::Nodes;

CollisionNode::CollisionNode(unsigned long id, const std::vector<sf::Vector2f> &pts)
	: Node(id), mPoints()
{
	for (int i = 0; i < pts.size(); i++)
	{
		mPoints.push_back(pts.at(i));
	}
}

CollisionNode::CollisionNode(unsigned long id, Node* parent, const std::vector<sf::Vector2f> &pts)
	: Node(id, parent), mPoints()
{
	for (int i = 0; i < pts.size(); i++)
	{
		mPoints.push_back(pts.at(i));
	}
}

int CollisionNode::isColliding(CollisionNode *node)
{
	//Needs future revision, and is not commented atm.
	std::vector<sf::Vector2f> tmPointsA;
	std::vector<sf::Vector2f> tmPointsB;

	Transformation::transform(this, mPoints, &tmPointsA);
	Transformation::transform(node, node->getPoints(), &tmPointsB);

	sf::Vector2f ulA, urA, lrA, llA;
	sf::Vector2f ulB, urB, lrB, llB;
	getBoundingPoints(&tmPointsA, &ulA, &lrA);
	getBoundingPoints(&tmPointsB, &ulB, &lrB);
	urA.x = lrA.x; urA.y = ulA.y;
	llA.x = ulA.x; llA.y = lrA.y;

	urB.x = lrB.x; urB.y = ulB.y;
	llB.x = ulB.x; llB.y = lrB.y;

	std::vector<sf::Vector2f> boundingA, boundingB;
	boundingA.push_back(urA);
	boundingA.push_back(ulA);
	boundingA.push_back(llA);
	boundingA.push_back(lrA);

	boundingB.push_back(urB);
	boundingB.push_back(ulB);
	boundingB.push_back(llB);
	boundingB.push_back(lrB);
	
	if (!polygonIntersects(&boundingA, &boundingB))
		return 0;
	else 
	{
		if (polygonIntersects(&tmPointsA, &tmPointsB))
			return 1;

		return 2;
	}
}

std::vector<sf::Vector2f> CollisionNode::getPoints()
{
	return std::vector<sf::Vector2f>(mPoints);
}

void CollisionNode::draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime)
{
	mDrawChildren(context, graphics, time, deltaTime);
}