//Version: 0.1.12
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_12
#error CollisionNode.cpp: Wrong Version 0.1.12
#endif

#include "CollisionNode.h"
#include "Transformation.h"
#include <glm\geometric.hpp>
#include <glm\gtx\intersect.hpp>

#include <SFML\OpenGL.hpp>

#include "HelpFunctions.h"

using namespace Angler;
using namespace Angler::HelpFunctions::Geometry;
using namespace Angler::Nodes;

CollisionNode::CollisionNode(unsigned long id, const std::vector<sf::Vector2f> &pts, int type)
	: Node(id), mPoints(), mType(type)
{
	for (unsigned int i = 0; i < pts.size(); i++)
	{
		mPoints.push_back(pts.at(i));
		mTransformedPoints.push_back(sf::Vector2f(-1, -1));
	}

	mBounding.push_back(sf::Vector2f(-1, -1));
	mBounding.push_back(sf::Vector2f(-1, -1));
	mBounding.push_back(sf::Vector2f(-1, -1));
	mBounding.push_back(sf::Vector2f(-1, -1));
	mUL = sf::Vector2f(-1, -1);
	mLR = sf::Vector2f(-1, -1);
}

CollisionNode::CollisionNode(unsigned long id, Node* parent, const std::vector<sf::Vector2f> &pts, int type)
	: Node(id, parent), mPoints(), mType(type)
{
	for (unsigned int i = 0; i < pts.size(); i++)
	{
		mPoints.push_back(pts.at(i));
		mTransformedPoints.push_back(sf::Vector2f(-1, -1));
	}

	mBounding.push_back(sf::Vector2f(-1, -1));
	mBounding.push_back(sf::Vector2f(-1, -1));
	mBounding.push_back(sf::Vector2f(-1, -1));
	mBounding.push_back(sf::Vector2f(-1, -1));
	mUL = sf::Vector2f(-1, -1);
	mLR = sf::Vector2f(-1, -1);
}

CollisionNode::~CollisionNode()
{
	mPoints.clear();
	mTransformedPoints.clear();
	mBounding.clear();

	Node::~Node();
}

int CollisionNode::getType()
{
	return mType;
}

int CollisionNode::isColliding(CollisionNode *node)
{
	/*if (mTransformedPoints.size() == 0)
		return 0;*/

	if (!(((mType == 0 && (node->mType == 0 || node->mType == 1)) || (node->mType == 0 && (mType == 0 || mType == 1)) ||
		(mType == 2 && (node->mType == 2 || node->mType == 3)) || (node->mType == 2 && (mType == 2 || mType == 3)))))
		return 0;

	/*if (!isSameRegion(mRegion, node->mRegion))
		return 0;*/

	if (!polygonIntersects(&mBounding, &node->mBounding))
		return 0;
	//if (!boundingCollides(mUL, mLR, node->mUL, node->mLR))
		//return 0;
	else
	{
		if (polygonIntersects(&mTransformedPoints, &node->mTransformedPoints))
			return 1;

		return 2;
	}
}

std::vector<sf::Vector2f> CollisionNode::getPoints()
{
	return std::vector<sf::Vector2f>(mPoints);
}

std::vector<sf::Vector2f> CollisionNode::getTransformedPoints()
{
	return std::vector<sf::Vector2f>(mTransformedPoints);
}

sf::Vector2f CollisionNode::getBoundingUL()
{
	return mUL;
}

sf::Vector2f CollisionNode::getBoundingLR()
{
	return mLR;
}

void CollisionNode::draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime)
{
	if (mVisible)
		mDrawChildren(context, graphics, time, deltaTime);
}

void CollisionNode::update(Game* context, float time, float deltaTime, bool changed)
{
	if (!mPaused)
	{
		mChanged |= changed;

		if (mChanged)
		{
			mTransformedPoints.clear();
			Transformation::transform(this, &mPoints, &mTransformedPoints);

			getBoundingPoints(&mTransformedPoints, &mUL, &mLR);
			mBounding.clear();
			mBounding.push_back(sf::Vector2f(mLR.x, mUL.y));
			mBounding.push_back(mUL);
			mBounding.push_back(sf::Vector2f(mUL.x, mLR.y));
			mBounding.push_back(mLR);
		}

		mUpdateChildren(context, time, deltaTime);
	}
}

void CollisionNode::setCollision(const std::vector<sf::Vector2f> &pts)
{
	mPoints.clear();
	for (unsigned int i = 0; i < pts.size(); i++)
	{
		mPoints.push_back(pts.at(i));
	}

	mTransformedPoints.clear();
	Transformation::transform(this, &mPoints, &mTransformedPoints);

	getBoundingPoints(&mTransformedPoints, &mUL, &mLR);
	mBounding.clear();
	mBounding.push_back(sf::Vector2f(mLR.x, mUL.y));
	mBounding.push_back(mUL);
	mBounding.push_back(sf::Vector2f(mUL.x, mLR.y));
	mBounding.push_back(mLR);

	mChanged = true;
}