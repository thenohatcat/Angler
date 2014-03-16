//Version: 0.1.11
//Author: Jakob Pipping
//Contributors:

#ifndef INC_SCALE_H
#define INC_SCALE_H

#ifdef ANGLER_0_1_11

#include "Transformation.h"

#include <SFML\System\Vector2.hpp>

namespace Angler
{
	namespace Nodes
	{
		class Scale
			: public Transformation
		{
		public:
			//Standard node constructors with a scale vector
			//(both in (float, float) and as a sf::Vector2f)
			Scale(unsigned long id, float scaleX, float scaleY);
			Scale(unsigned long id, sf::Vector2f s);

			Scale(unsigned long id, Node *parent, float scaleX, float scaleY);
			Scale(unsigned long id, Node *parent, sf::Vector2f s);

			//Sets the current scale
			void setScale(float scaleX, float scaleY);
			void setScale(sf::Vector2f s);

			//Scales the current scale
			void scale(float scaleX, float scaleY);
			void scale(sf::Vector2f s);

			sf::Vector2f getScale();
			float getScaleX(), getScaleY();

			//The transformation itself, to standardize functionality
			void doTransform();

			void doInverseTransform();

		private:
			float mScaleX, mScaleY;
		};
	}
}

#else
#error Scale.h: Wrong Version 0.1.11
#endif

#endif