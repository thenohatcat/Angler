//Version: 0.1.12
//Author: Jakob Pipping
//Contributors:

#ifndef INC_TRANSLATION_H
#define INC_TRANSLATION_H

#ifdef ANGLER_0_1_12

#include "Transformation.h"

#include <SFML\System\Vector2.hpp>

namespace Angler
{
	namespace Nodes
	{
		//Transformation node for translation
		class Translation
			: public Transformation
		{
		public:
			//Standard node constructors with a translation vector
			//(both in (float, float) and as a sf::Vector2f)
			Translation(unsigned long id, float x, float y);
			Translation(unsigned long id, sf::Vector2f translation);

			Translation(unsigned long id, Node *parent, float x, float y);
			Translation(unsigned long id, Node *parent, sf::Vector2f translation);

			//Used to force the current translation value
			void setTranslation(float x, float y);
			void setTranslation(sf::Vector2f translation);

			//Does a relative translation to the current one (adds)
			void translate(float x, float y);
			void translate(sf::Vector2f translation);

			sf::Vector2f getTranslation();
			float getTranslationX(), getTranslationY();

			//The transformation itself, to standardize functionality
			void doTransform();

			void doInverseTransform();

		private:
			float mX, mY;
		};
	}
}

#else
#error Transformation.h: Wrong Version 0.1.12
#endif

#endif