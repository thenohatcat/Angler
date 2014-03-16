//Version: 0.1.11
//Author: Jakob Pipping
//Contributors: 

#ifndef INC_ANIMATEDNODE_H
#define INC_ANIMATEDNODE_H

#ifdef ANGLER_0_1_11

#include "SpriteNode.h"

namespace Angler
{
	namespace Nodes
	{
		class AnimatedNode
			: public SpriteNode
		{
		public:
			//Creates an animated node with a parent
			AnimatedNode(unsigned long id, Node *parent, int layer,
				std::vector<sf::Vector2f> &pts, float frametime, float ox = 0, float oy = 0, float cropWidth = 1, float cropHeight = 1);

			//Creates an animated node
			AnimatedNode(unsigned long id, int layer,
				std::vector<sf::Vector2f> &pts, float frametime, float ox = 0, float oy = 0, float cropWidth = 1, float cropHeight = 1);

			virtual ~AnimatedNode();

			void update(Game *context, float time, float deltaTime, bool changed = false);

			void setFrame(int f);

		protected:
			//Current frame
			int mFrame;
			//Elapsed time in seconds
			float mTime;
			//Number of seconds per frame
			float mFrameTime;
			//Crop origin points for the frames
			std::vector<sf::Vector2f> mPts;
		};
	}
}

#else
#error AnimatedNode.h: Wrong Version 0.1.11
#endif

#endif