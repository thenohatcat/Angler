//Version: 0.1.4
//Author: Jakob Pipping
//Contributors: 

#ifndef INC_SPRITEENGINE_H
#define INC_SPRITEENGINE_H

#ifdef ANGLER_0_1_4

#include "DrawNode.h"

namespace Angler
{
	namespace Nodes
	{
		class SpriteNode
			: public DrawNode
		{
		public:
			SpriteNode(unsigned long id, Node *parent, int layer, sf::Texture *tx, 
				float ox = 0, float oy = 0, float cropOriginX = 0, float cropOriginY = 0, 
				float cropWidth = 1, float cropHeight = 1);
			SpriteNode(unsigned long id, Node *parent, int layer, sf::Texture *tx, 
				sf::Vector2f origo, 
				sf::Vector2f cropOrigin, 
				sf::Vector2f cropSize);

			SpriteNode(unsigned long id, int layer, sf::Texture *tx, 
				float ox = 0, float oy = 0, float cropOriginX = 0, float cropOriginY = 0, 
				float cropWidth = 1, float cropHeight = 1);
			SpriteNode(unsigned long id, int layer, sf::Texture *tx, 
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
#error SpriteEngine.h: Wrong Version 0.1.4
#endif

#endif