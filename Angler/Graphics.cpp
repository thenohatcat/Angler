//Version: 0.1.5
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_5
#error Graphics.cpp: Wrong Version 0.1.5
#endif

#include "Graphics.h"
#include "Game.h"

#include <SFML\Graphics.hpp>
#include <glut.h>
#include <vector>

#include "Exceptions.h"

using namespace Angler;
using namespace Angler::Graphics;
using namespace Angler::Exceptions::Graphics;

GraphicsEngine::GraphicsEngine(Game *parent, int numLayers)
	: mParent(parent), mNumLayers(numLayers), mRunning(false)
{
	mLayers = new GraphicElement**[mNumLayers];
	mIndx = new int[mNumLayers];

	for (int layer = 0; layer < mNumLayers; layer++)
	{
		mLayers[layer] = new GraphicElement*[MAX_ELEMENTS];
		for (int i = 0; i < MAX_ELEMENTS; i++)
		{
			mLayers[layer][i] = new GraphicElement();
		}
		mIndx[layer] = 0;
	}
}

GraphicsEngine::~GraphicsEngine()
{
	delete[] mLayers;
}

void GraphicsEngine::createWindow(int width, int height, const char* title, bool resizable)
{
	//Creates a SFML window
	mWindow = new sf::RenderWindow(sf::VideoMode(width, height), title, 
		(resizable ? sf::Style::Resize : sf::Style::Close));
}

void GraphicsEngine::begin()
{
	if (!mRunning)
	{
		mClear();

		mRunning = true;

		mOldTexture = nullptr;

		//Must be done every frame, as SFML does it's own wiewframe code
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float(getWidth()) / float(getHeight())), 1, 0, 0.5, 10);

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//Z is depth, x and y are x and y respectively
		gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	}
	else
	{
		//If we call begin during a draw cycle (when mRunning == true)
		throw graphics_begin_without_end_exception();
	}
}

void GraphicsEngine::display()
{
	//Swaps the display buffers and renders to the screen
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
		//If we call end outside of a draw cycle (when mRunning == false)
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

		*(mLayers[layer][mIndx[layer]++]) = GraphicElement(matrix, originX, originY, 
			cropOriginX, cropOriginY, cropWidth, cropHeight,
			r, g, b, a, tx);
	}
	else
	{
		//Thrown if draw is called outside of the draw cycle (mRunning == false)
		throw graphics_draw_without_begin_exception();
	}
}

//Multiple draw functions, with the default values of:
//Origin: (0, 0)
//Color: (1, 1, 1, 1)
//Crop Origin: (0, 0)
//Crop Size: (1, 1)
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

void GraphicsEngine::draw(int layer, sf::Texture *tx)
{
	draw(layer, tx, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1);
}

void GraphicsEngine::resize(int width, int height)
{
	//Updates the viewport to fit the current size
	glViewport(0, 0, width, height);
}

void GraphicsEngine::mClear()
{
	for (int layer = 0; layer < mNumLayers; layer++)
	{
		mIndx[layer] = 0;
	}
}

void GraphicsEngine::mRender()
{
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//Iterates over each layer, back to front, and renders all elements
	for (int layer = 0; layer < mNumLayers; layer++)
	{
		for (int i = 0; i < mIndx[layer]; i++)
		{
			mDrawElement(mLayers[layer][i]);
		}
	}
	glPopMatrix();
}

void GraphicsEngine::mDrawElement(GraphicElement *element)
{
	if (mOldTexture != element->mTexture)
	{
		sf::Texture::bind(element->mTexture);
		mOldTexture = element->mTexture;
	}

	glPushMatrix();
	//Loads the matrix stored in element into graphics
	glLoadMatrixd(element->mMatrix);

	//Sets the current color
	glColor4d(element->mR, element->mG, element->mB, element->mA);
	//Calculates aspect ratio
	float ar = (element->mTexture->getSize().x /
		(double)element->mTexture->getSize().y);
	//If cropHeight and cropWidht isn't the default value we calculate that 
	//aspect ratio instead
	if (element->mCropOriginX != 0 || element->mCropOriginY != 0 ||
		element->mCropHeight != 1 || element->mCropWidth != 1)
		ar = (element->mCropWidth / element->mCropHeight);
	//Scales based on aspect ratio
	glScaled(ar, 1, 1);

	//Translates so we get our origin
	glTranslated(-element->mOriginX, -element->mOriginY, 0);
	//Draws the quad, with the texture coordinates based on the crop
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
	//Uses SFML
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

void GraphicsEngine::close()
{
	mWindow->close();
}