//Version: 0.1.11
//Author: Jakob Pipping
//Contributors:

#ifndef INC_ROTATION_H
#define INC_ROTATION_H

#ifdef ANGLER_0_1_11

#include "Transformation.h"

namespace Angler
{
	namespace Nodes
	{
		class Rotation
			: public Transformation
		{
		public:
			//Standard node constructors with a rotation
			Rotation(unsigned long id, float rotation);

			Rotation(unsigned long id, Node *parent, float rotation);

			//Sets the current rotation
			void setRotation(float rot);

			//Rotates (adds) the current rotation
			void rotate(float rot);

			float getRotation();

			//The transformation itself, to standardize functionality
			void doTransform();

			void doInverseTransform();

		private:
			float mRotation;
		};
	}
}

#else
#error Rotation.h: Wrong Version 0.1.11
#endif

#endif