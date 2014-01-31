//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_1
#error Graphics.cpp: Wrong Version 0.1.1
#endif

#include "Graphics.h"
#include "Game.h"

#include <SFML\Graphics.hpp>
#include <glut.h>
#include <vector>

#include "Exceptions.h"

using namespace Angler;
using namespace Angler::Graphics;
using namespace Angler::Exceptions;

GraphicsEngine::GraphicsEngine(Game *parent, int numLayers)
	: mParent(parent), mNumLayers(numLayers), 
	mLayers(new GraphicElementVector[numLayers]), mRunning(false)
{
	for (int layer = 0; layer < mNumLayers; layer++)
	{
		mLayers[layer] = GraphicElementVector(MAX_ELEMENTS);
		mLayers[layer].clear();
	}
}

GraphicsEngine::~GraphicsEngine()
{
	delete[] mLayers;
}

void GraphicsEngine::createWindow(int width, int height, const char* title, bool resizable)
{
	mWindow = new sf::RenderWindow(sf::VideoMode(width, height), title, 
		(resizable ? sf::Style::Resize : sf::Style::Close));
}

void GraphicsEngine::begin()
{
	if (!mRunning)
	{
		mClear();

		mRunning = true;

		//Must be done every frame, as SFML creates it's own 
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float(getWidth()) / float(getHeight())), 1, 0, 0.5, 10);

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	}
	else
	{
		throw graphics_begin_without_end_exception();
	}
}

void GraphicsEngine::display()
{
	mWindow->display();
}

void GraphicsEngine::end()
{
	if (mRunning)
	{
		mRender();

		mRunning = false;
	}
	else
	{
		throw graphics_end_without_begin_exception();
	}
}

void GraphicsEngine::draw(int layer, sf::Texture *tx, float originX, float originY, 
					float cropOriginX, float cropOriginY, float cropWidth, float cropHeight,
					float r, float g, float b, float a)
{
	if (mRunning)
	{
		//Reads the modelview matrix to be used in a GraphicsElement
		GLdouble matrix[16];
		glGetDoublev(GL_MODELVIEW_MATRIX, matrix);

		mLayers[layer].push_back(new GraphicElement(matrix, originX, originY, 
			cropOriginX, cropOriginY, cropWidth, cropHeight,
			r, g, b, a, tx));
	}
	else
	{
		throw graphics_draw_without_begin_exception();
	}
}

void GraphicsEngine::draw(int layer, sf::Texture *tx, sf::Vector2f origin, sf::Vector2f cropOrigin,
					sf::Vector2f cropSize, float r, float g, float b, float a)
{
	draw(layer, tx, origin.x, origin.y, cropOrigin.x, cropOrigin.y, cropSize.x, cropSize.y, r, g, b, a);
}

void GraphicsEngine::draw(int layer, sf::Texture *tx, float originX, float originY, 
					float r, float g, float b, float a)
{
	draw(layer, tx, originX, originY, 0, 0, 1, 1, r, g, b, a);
}

void GraphicsEngine::draw(int layer, sf::Texture *tx, sf::Vector2f origin,
					float r, float g, float b, float a)
{
	draw(layer, tx, origin.x, origin.y, 0, 0, 1, 1, r, g, b, a);
}

void GraphicsEngine::draw(int layer, sf::Texture *tx, sf::Vector2f cropOrigin, sf::Vector2f cropSize)
{
	draw(layer, tx, 0, 0, cropOrigin.x, cropOrigin.y, cropSize.x, cropSize.y, 1, 1, 1, 1);
}

void GraphicsEngine::draw(int layer, sf::Texture *tx, sf::Vector2f origin, sf::Vector2f cropOrigin,
					sf::Vector2f cropSize)
{
	draw(layer, tx, origin.x, origin.y, cropOrigin.x, cropOrigin.y, cropSize.x, cropSize.y, 
		1, 1, 1, 1);
}

void GraphicsEngine::draw(int layer, sf::Texture *tx, sf::Vector2f origin)
{
	draw(layer, tx, origin.x, origin.y);
}

void GraphicsEngine::draw(int layer, sf::Texture *tx, float r, float g, float b, 
						 float a)
{
	draw(layer, tx, 0, 0, 0, 0, 1, 1, r, g, b, a);
}

void GraphicsEngine::draw(int layer, sf::Texture *tx, float originX, float originY)
{
	draw(layer, tx, originX, originY, 0, 0, 1, 1, 1, 1, 1, 1);
}

void GraphicsEngine::resize(int width, int height)
{
	glViewport(0, 0, width, height);
}

void GraphicsEngine::mClear()
{
	for (int layer = 0; layer < mNumLayers; layer++)
	{
		mLayers[layer].clear();
	}
}

void GraphicsEngine::mRender()
{
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	for (int layer = 0; layer < mNumLayers; layer++)
	{
		for (GraphicElementVector::const_iterator element = mLayers[layer].begin(); 
			element != mLayers[layer].end(); element++)
		{
			mDrawElement(*element);
		}
	}
	glPopMatrix();
}

void GraphicsEngine::mDrawElement(GraphicElement *element)
{
	sf::Texture::bind(element->mTexture);

	glPushMatrix();
	glLoadMatrixd(element->mMatrix);

	glColor4d(element->mR, element->mG, element->mB, element->mA);
	float ar = (element->mTexture->getSize().x /
		(double)element->mTexture->getSize().y);
	if (element->mCropHeight != 0 && element->mCropWidth != 0)
		ar = (element->mCropWidth / element->mCropHeight);
	glScaled(ar, 1, 1);

	glTranslated(-element->mOriginX, -element->mOriginY, 0);
	glBegin(GL_QUADS);
		glTexCoord2d(element->mCropOriginX, element->mCropOriginY + element->mCropHeight);
		glVertex2d(0, 1);
		glTexCoord2d(element->mCropOriginX, element->mCropOriginY);
		glVertex2d(0, 0);
		glTexCoord2d(element->mCropOriginX + element->mCropWidth, element->mCropOriginY);
		glVertex2d(1, 0);
		glTexCoord2d(element->mCropOriginX + element->mCropWidth, element->mCropOriginY + element->mCropHeight);
		glVertex2d(1, 1);
	glEnd();
	glPopMatrix();
}

void GraphicsEngine::loadTexture(sf::Texture* texture, const char* fileName)
{
	texture->loadFromFile(fileName);
}

int GraphicsEngine::getWidth()
{
	return mWindow->getSize().x;
}

int GraphicsEngine::getHeight()
{
	return mWindow->getSize().y;
}