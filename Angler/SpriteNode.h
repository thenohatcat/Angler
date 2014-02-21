//Version: 0.1.8
//Author: Jakob Pipping
//Contributors: 

#ifndef INC_SPRITENODE_H
#define INC_SPRITENODE_H

#ifdef ANGLER_0_1_8

#include "DrawNode.h"

namespace Angler
{
	namespace Nodes
	{
		class SpriteNode
			: public DrawNode
		{
		public:
			SpriteNode(unsigned long id, Node *parent, int layer, float ox = 0, float oy = 0, 
				float cropOriginX = 0, float cropOriginY = 0, 
				float cropWidth = 1, float cropHeight = 1);
			SpriteNode(unsigned long id, Node *parent, int layer, 
				sf::Vector2f origo, sf::Vector2f cropOrigin, 
				sf::Vector2f cropSize);

			SpriteNode(unsigned long id, int layer, 
				float ox = 0, float oy = 0, float cropOriginX = 0, float cropOriginY = 0, 
				float cropWidth = 1, float cropHeight = 1);
			SpriteNode(unsigned long id, int layer, 
				sf::Vector2f origo, 
				sf::Vector2f cropOrigin, 
				sf::Vector2f cropSize);

			void setCropOrigin(float x, float y);
			void setCropOrigin(sf::Vector2f origin);

			float getCropOriginX();
			float getCropOriginY();
			sf::Vector2f getCropOrigin();

			void setCropSize(float w, float h);
			void setCropSize(sf::Vector2f size);

			float getCropWidth();
			float getCropHeight();
			sf::Vector2f getCropSize();
			
			void draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime);

		protected:
			float mCropOriginX, mCropOriginY, mCropWidth, mCropHeight;
		};
	}
}

#else
#error SpriteNode.h: Wrong Version 0.1.8
#endif

#endif