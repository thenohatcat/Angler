//Version: 0.1.12
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_12
#error GraphicsLayer.cpp: Wrong Version 0.1.12
#endif

#include "Graphics.h"
#include "HelpFunctions.h"

using namespace Angler;
using namespace Angler::Graphics;

GraphicsLayer::GraphicsLayer(GraphicsEngine *owner, int numElements, int cropX, int cropY, int cropW, int cropH)
	: mOwner(owner), mNumElements(numElements), mBuffVertex(new GLfloat[numElements*8]), 
	mBUffColor(new GLfloat[numElements*16]), mBuffTexCord(new GLfloat[numElements*8]),
	mCropX(cropX), mCropY(cropY), mCropW(cropW), mCropH(cropH), mIndx(0)
{

}

void GraphicsLayer::setTexture(sf::Texture *tx)
{
	mTexture = tx;
	mTextureAR = (tx->getSize().x / (float)tx->getSize().y);
}

void GraphicsLayer::clear()
{
	mIndx = 0;
}

void GraphicsLayer::render()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	sf::Texture::bind(mTexture);

	glPushMatrix();
	glViewport(mCropX, (mOwner->getHeight()-mCropH) - mCropY, mCropW, mCropH);
	glScalef((float)(mOwner->getWidth())/mCropW, (float)(mOwner->getHeight())/mCropH, 1);
	glTranslatef(-mCropX/(float)(mOwner->getHeight()), -mCropY/(float)(mOwner->getHeight()), 0);

	glVertexPointer(2, GL_FLOAT, 0, mBuffVertex);
	glTexCoordPointer(2, GL_FLOAT, 0, mBuffTexCord);
	glColorPointer(4, GL_FLOAT, 0, mBUffColor);
	glDrawArrays(GL_QUADS, 0, mIndx * 4);

	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void GraphicsLayer::setCrop(int x, int y, int w, int h)
{
	mCropX = x;
	mCropY = y;
	mCropW = w;
	mCropH = h;
}

void GraphicsLayer::draw(float originX, float originY, float cropOriginX, float cropOriginY, 
						 float cropWidth, float cropHeight, float r, float g, float b, float a)
{
	glPushMatrix();

	float ar = 1;
	//If cropHeight and cropWidht isn't the default value we calculate that 
	//aspect ratio instead
	if (cropOriginX != 0 || cropOriginY != 0 ||
		cropHeight != 1 || cropWidth != 1)
		ar = (mTextureAR * cropWidth / cropHeight);
	else
		ar = mTextureAR;
	//Scales based on aspect ratio
	glScalef(ar, 1, 1);

	//Translates so we get our origin
	glTranslatef(-originX, -originY, 0);
	//Draws the quad, with the texture coordinates based on the crop

	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix);

	sf::Vector2f vcts[] =
	{
		sf::Vector2f(0, 1),
		sf::Vector2f(0, 0),
		sf::Vector2f(1, 0),
		sf::Vector2f(1, 1)
	};

	for (int k = 0; k < 4; k++)
	{
		vcts[k] = HelpFunctions::Geometry::transform(mMatrix, vcts[k]);
	}

	mBUffColor[mIndx*16 + 0] = r;
	mBUffColor[mIndx*16 + 1] = g;
	mBUffColor[mIndx*16 + 2] = b;
	mBUffColor[mIndx*16 + 3] = a;
	mBUffColor[mIndx*16 + 4] = r;
	mBUffColor[mIndx*16 + 5] = g;
	mBUffColor[mIndx*16 + 6] = b;
	mBUffColor[mIndx*16 + 7] = a;
	mBUffColor[mIndx*16 + 8] = r;
	mBUffColor[mIndx*16 + 9] = g;
	mBUffColor[mIndx*16 + 10] = b;
	mBUffColor[mIndx*16 + 11] = a;
	mBUffColor[mIndx*16 + 12] = r;
	mBUffColor[mIndx*16 + 13] = g;
	mBUffColor[mIndx*16 + 14] = b;
	mBUffColor[mIndx*16 + 15] = a;

	mBuffVertex[mIndx*8 + 0] = vcts[0].x;
	mBuffVertex[mIndx*8 + 1] = vcts[0].y;
	mBuffVertex[mIndx*8 + 2] = vcts[1].x;
	mBuffVertex[mIndx*8 + 3] = vcts[1].y;
	mBuffVertex[mIndx*8 + 4] = vcts[2].x;
	mBuffVertex[mIndx*8 + 5] = vcts[2].y;
	mBuffVertex[mIndx*8 + 6] = vcts[3].x;
	mBuffVertex[mIndx*8 + 7] = vcts[3].y;

	mBuffTexCord[mIndx*8 + 0] = cropOriginX;
	mBuffTexCord[mIndx*8 + 1] = cropOriginY + cropHeight;
	mBuffTexCord[mIndx*8 + 2] = cropOriginX;
	mBuffTexCord[mIndx*8 + 3] = cropOriginY;
	mBuffTexCord[mIndx*8 + 4] = cropOriginX + cropWidth;
	mBuffTexCord[mIndx*8 + 5] = cropOriginY;
	mBuffTexCord[mIndx*8 + 6] = cropOriginX + cropWidth;
	mBuffTexCord[mIndx*8 + 7] = cropOriginY + cropHeight;
	mIndx++;

	glPopMatrix();
}