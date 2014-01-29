#include "Graphics.h"

GraphicElement::GraphicElement(GLdouble matrix[16], float originX, float originY, 
							   float r, float g, float b, float a, 
							   sf::Texture *texture)
							   : mR(r), mG(g), mB(b), mA(a), mTexture(texture),
							   mOriginX(originX), mOriginY(originY)
{
	mMatrix[ 0] = matrix[ 0]; mMatrix[ 1] = matrix[ 1]; mMatrix[ 2] = matrix[ 2];
	mMatrix[ 3] = matrix[ 3]; mMatrix[ 4] = matrix[ 4]; mMatrix[ 5] = matrix[ 5];
	mMatrix[ 6] = matrix[ 6]; mMatrix[ 7] = matrix[ 7]; mMatrix[ 8] = matrix[ 8];
	mMatrix[ 9] = matrix[ 9]; mMatrix[10] = matrix[10]; mMatrix[11] = matrix[11];
	mMatrix[12] = matrix[12]; mMatrix[13] = matrix[13]; mMatrix[14] = matrix[14];
	mMatrix[15] = matrix[15];
}