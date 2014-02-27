//Version: 0.1.9
//Author: Jakob Pipping
//Contributors:

#ifndef INC_DRAWNODE_H
#define INC_DRAWNODE_H

#ifdef ANGLER_0_1_9

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
			//Creates a new draw node with a parent
			DrawNode(unsigned long id, Node *parent, int layer, float ox = 0, float oy = 0);

			//Creates a new draw node with a parent, using vectors
			DrawNode(unsigned long id, Node *parent, int layer, sf::Vector2f origo);

			//Creates a new draw node
			DrawNode(unsigned long id, int layer, float ox = 0, float oy = 0);
			//Creates a new draw node, using vectors
			DrawNode(unsigned long id, int layer, sf::Vector2f origo);

			virtual ~DrawNode();

			void draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime);

			//Sets the origin point of the node
			void setOrigin(sf::Vector2f origin);
			void setOrigin(float x, float y);
			sf::Vector2f getOrigin();
			float getOriginX();
			float getOriginY();

		protected:
			//The layer of the draw node
			int mLayer;
			//The origin of the node
			float mOX, mOY;
		};
	}
}

#else
#error DrawNode.h: Wrong Version 0.1.9
#endif

#endif