//Version: 0.1.9
//Author: Jakob Pipping
//Contributors: 

#ifndef ANGLER_0_1_9
#error AnimatedNode.cpp: Wrong Version 0.1.9
#endif

#include "AnimatedNode.h"

using namespace Angler;
using namespace Angler::Nodes;

AnimatedNode::AnimatedNode(unsigned long id, Node *parent, int layer, std::vector<sf::Vector2f> &pts, 
						   float frametime, float ox, float oy, float cropWidth, float cropHeight)
				: SpriteNode(id, parent, layer, ox, oy, 0, 0, cropWidth, cropHeight), mFrame(0), 
				mFrameTime(frametime), mTime(0)
{
	for (unsigned int i = 0; i < pts.size(); i++)
	{
		mPts.push_back(pts.at(i));
	}
}

AnimatedNode::AnimatedNode(unsigned long id, int layer, std::vector<sf::Vector2f> &pts, 
						   float frametime, float ox, float oy, float cropWidth, float cropHeight)
				: SpriteNode(id, layer, ox, oy, 0, 0, cropWidth, cropHeight), mFrame(0), 
				mFrameTime(frametime), mTime(0)
{
	for (unsigned int i = 0; i < pts.size(); i++)
	{
		mPts.push_back(pts.at(i));
	}
}

AnimatedNode::~AnimatedNode()
{
	mPts.clear();

	Node::~Node();
}

void AnimatedNode::update(Game *context, float time, float deltaTime, bool changed)
{
	if (!mPaused)
	{
		setCropOrigin(mPts.at(mFrame));

		mFrame = (int)(mTime / mFrameTime) % mPts.size();

		mTime += deltaTime;

		mUpdateChildren(context, time, deltaTime);
	}
}