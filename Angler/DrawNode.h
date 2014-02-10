//Version: 0.1.5
//Author: Jakob Pipping
//Contributors:

#ifndef INC_DRAWNODE_H
#define INC_DRAWNODE_H

#ifdef ANGLER_0_1_5

#include "Node.h"
#include "Graphics.h"
#include <SFML\Graphics\Texture.hpp>

namespace Angler
{
	namespace Nodes
	{
		//A draw node that renders sf::Textures (currently)
		class DrawNode
			: public Node
		{
		public:
			//Standard constructors, with a layer for the texture, a pointer to a texture and
			//a origin vector (both in (float, float) and as a sf::Vector2f)
			DrawNode(unsigned long id, Node *parent, int layer, sf::Texture *tx, float ox = 0, float oy = 0);
			DrawNode(unsigned long id, Node *parent, int layer, sf::Texture *tx, sf::Vector2f origo);

			DrawNode(unsigned long id, int layer, sf::Texture *tx, float ox = 0, float oy = 0);
			DrawNode(unsigned long id, int layer, sf::Texture *tx, sf::Vector2f origo);

			void draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime);

			void setOrigin(sf::Vector2f origin);
			void setOrigin(float x, float y);
			sf::Vector2f getOrigin();
			float getOriginX();
			float getOriginY();

		protected:
			int mLayer;
			sf::Texture *mTX;
			float mOX, mOY;
		};
	}
}

#else
#error DrawNode.h: Wrong Version 0.1.5
#endif

#endif