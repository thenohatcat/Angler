//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

//Changelog:
//changed parent class to Transformation
//+ added		void rotate(float)
//+ added		float getRotation()
//renamed		updateRotation to setRotation
//+ added		doTransform()

#ifndef INC_ROTATION_H
#define INC_ROTATION_H

#ifdef ANGLER_0_1_1

#include "Transformation.h"

namespace Angler
{
	namespace Nodes
	{
		class Rotation
			: public Transformation
		{
		public:
			Rotation(float rotation);

			Rotation(Node *parent, float rotation);

			void setRotation(float rot);

			void rotate(float rot);

			float getRotation();

			virtual void draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime);

			void doTransform();

		private:
			float mRotation;
		};
	}
}

#else
#error Rotation.h: Wrong Version 0.1.1
#endif

#endif