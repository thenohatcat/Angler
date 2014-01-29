#include "Graphics.h"
#include "Game.h"

#include <SFML\Graphics.hpp>
#include <glut.h>
#include <vector>

Graphics::Graphics(Game *parent)
	: mParent(parent), mLayers(new GraphicElementVector[parent->mNumLayers])
{
	for (int layer = 0; layer < parent->mNumLayers; layer++)
	{
		mLayers[layer] = GraphicElementVector(MAX_ELEMENTS);
		mLayers[layer].clear();
	}
}

Graphics::~Graphics()
{
	mParent = NULL;
	delete[] mLayers;
}

void Graphics::begin()
{
	if (!mRunning)
	{
		mClear();

		mRunning = true;
	}
	else
	{

	}
}

void Graphics::end()
{
	if (mRunning)
	{
		mRender();

		mRunning = false;
	}
	else
	{

	}
}

void Graphics::draw(int layer, sf::Texture *tx, float originX, float originY, 
					float r, float g, float b, float a)
{
	GLdouble matrix[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);

	mLayers[layer].push_back(new GraphicElement(matrix, originX, originY, r, g, b, a, tx));
}

void Graphics::draw(int layer, sf::Texture *tx, float originX, float originY)
{
	draw(layer, tx, originX, originY, 1, 1, 1, 1);
}

void Graphics::draw(int layer, sf::Texture *tx, float r, float g, float b, 
						 float a)
{
	draw(layer, tx, 0, 0, r, g, b, a);
}

void Graphics::draw(int layer, sf::Texture *tx)
{
	draw(layer, tx, 0, 0, 1, 1, 1, 1);
}

void Graphics::mClear()
{
	for (int layer = 0; layer < mParent->mNumLayers; layer++)
	{
		mLayers[layer].clear();
	}
}

void Graphics::mRender()
{
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	for (int layer = 0; layer < mParent->mNumLayers; layer++)
	{
		for (GraphicElementVector::const_iterator element = mLayers[layer].begin(); 
			element != mLayers[layer].end(); element++)
		{
			mDrawElement(*element);
		}
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Graphics::mDrawElement(GraphicElement *element)
{
	sf::Texture::bind(element->mTexture);

	glLoadMatrixd(element->mMatrix);

	glColor4d(element->mR, element->mG, element->mB, element->mA);
	glScaled((element->mTexture->getSize().x / 
		(double)element->mTexture->getSize().y), 1, 1);

	
	glPushMatrix();
	glTranslated(-element->mOriginX, -element->mOriginY, 0);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2d(0, 1);
		glTexCoord2d(0, 0);
		glVertex2d(0, 0);
		glTexCoord2d(1, 0);
		glVertex2d(1, 0);
		glTexCoord2d(1, 1);
		glVertex2d(1, 1);
	glEnd();
	glPopMatrix();
}