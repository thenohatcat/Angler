//Version: 0.1.4
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_4
#error GraphicsElement.cpp: Wrong Version 0.1.4
#endif

#include "Graphics.h"

using namespace Angler::Graphics;

GraphicElement::GraphicElement(GLdouble matrix[16], float originX, float originY, 
							   float cropOriginX, float cropOriginY, 
							   float cropWidth, float cropHeight,
							   float r, float g, float b, float a, 
							   sf::Texture *texture)
							   : mR(r), mG(g), mB(b), mA(a), mTexture(texture),
							   mOriginX(originX), mOriginY(originY),
							   mCropOriginX(cropOriginX), mCropOriginY(cropOriginY),
							   mCropWidth(cropWidth), mCropHeight(cropHeight)
{
	memcpy(mMatrix, matrix, 16 * sizeof(GLdouble));
}

GraphicElement::GraphicElement()
{

}