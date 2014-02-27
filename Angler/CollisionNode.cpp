//Version: 0.1.9
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_9
#error CollisionNode.cpp: Wrong Version 0.1.9
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

bool isSameRegion(unsigned int rA, unsigned int rB)
{
	for (int i = 0; i < 7; i++)
	{
		if ((rA & 0xE) == 0 || (rB & 0xE) == 0)
			return true;
		if ((rA & 0xE) != (rB & 0xE))
			return false;

		rA = rA >> 3;
		rB = rB >> 3;
	}
	return true;
}

int CollisionNode::getType()
{
	return mType;
}

int CollisionNode::isColliding(CollisionNode *node)
{
	/*if (mTransformedPoints.size() == 0)
		return 0;*/

	if (mType != 0 && node->mType != 0)
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
	mDrawChildren(context, graphics, time, deltaTime);
}

unsigned long region(sf::Vector2f ul, sf::Vector2f lr)
{
	float w = 16/10.0f, h = 0.5f;
	unsigned int rtr = 0;
	float ulx = ul.x, uly = ul.y;
	float lrx = lr.x, lry = lr.y;
	unsigned int mult = 0x1; 
	unsigned int rg = 0;
	for (int i = 0; i < 7; i++)
	{
		//Col. 1
		if ((ulx < w) && (lrx < w))
		{
			ulx *= 2;
			lrx *= 2;
			//Row. 1
			if ((uly < h) && (lry < h))
			{
				uly *= 2;
				lry *= 2;
				rg = 0x4;
			}
			//Row. 2
			else if ((uly > h) && (lry > h))
			{
				uly = (uly - h) * 2.0f;
				lry = (lry - h) * 2.0f;
				rg = 0x6;
			}
			else
			{
				rg = 0x0;
			}
		}
		//Col. 2
		else if ((ulx > w) && (lrx > w))
		{
			ulx = (ulx - w) * 2.0f;
			lrx = (lrx - w) * 2.0f;
			//Row. 1
			if ((uly < h) && (lry < h))
			{
				uly *= 2;
				lry *= 2;
				rg = 0x5;
			}
			//Row. 2
			else if ((uly > h) && (lry > h))
			{
				uly = (uly - h) * 2.0f;
				lry = (lry - h) * 2.0f;
				rg = 0x7;
			}
			else
			{
				rg = 0x0;
			}
		}
		else
		{
			rg = 0x0;
		}

		if (rg != 0)
		{
			rtr += rg * mult;
			mult = mult << 3;
		}
		else
			break;
	}
	return rtr;
}

void CollisionNode::update(Game* context, float time, float deltaTime, bool changed)
{
	mChanged |= changed;

	if (mChanged)
	{
		mTransformedPoints.clear();
		Transformation::transform(this, mPoints, &mTransformedPoints);

		getBoundingPoints(&mTransformedPoints, &mUL, &mLR);
		mBounding.clear();
		mBounding.push_back(sf::Vector2f(mLR.x, mUL.y));
		mBounding.push_back(mUL);
		mBounding.push_back(sf::Vector2f(mUL.x, mLR.y));
		mBounding.push_back(mLR);

		//mRegion = region(mUL, mLR);
	}

	mUpdateChildren(context, time, deltaTime);
}