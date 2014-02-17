//Version: 0.1.7
//Author: Jakob Pipping
//Contributors:

#ifndef INC_TRANSFORMATION_H
#define INC_TRANSFORMATION_H

#ifdef ANGLER_0_1_7

#include "Node.h"

#include <SFML\System\Vector2.hpp>

namespace Angler
{
	namespace Nodes
	{
		class Transformation
			: public Angler::Node
		{
		public:
			//Standard node constructors
			Transformation(unsigned long id);
			Transformation(unsigned long id, Node *parent);

			//Transforms a lone vector with this object
			sf::Vector2f transform(sf::Vector2f v);

			//Transform a vector/array of points with this object
			void transform(sf::Vector2f *vIn, sf::Vector2f *vOut, int count);
			void transform(std::vector<sf::Vector2f> vIn, std::vector<sf::Vector2f> *vOut);

			//Static transformation of a node
			static void transform(Node *node);
			//Static transformation of a node on a vector/array of points
			static void transform(Node *node, sf::Vector2f *vIn, sf::Vector2f *vOit, int count);
			static void transform(Node *node, std::vector<sf::Vector2f> vIn, 
				std::vector<sf::Vector2f> *vOut);

			virtual void draw(Game *context, Graphics::GraphicsEngine *graphics, 
				float time, float deltaTime);

			//Virtual function to be used by derived classes
			virtual void doTransform() = 0;
		};
	}
}

#else
#error Transformation.h: Wrong Version 0.1.7
#endif

#endif