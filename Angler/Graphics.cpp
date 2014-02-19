//Version: 0.1.8
//Author: Jakob Pipping
//Contributors:

#ifndef ANGLER_0_1_8
#error Graphics.cpp: Wrong Version 0.1.8
#endif

#include <chrono>

#include <iostream>

#include <GL\glew.h>

#include "Graphics.h"
#include "Game.h"

#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include <vector>

#include <gl\GL.h>
#include <gl\GLU.h>

#include "Exceptions.h"

#include "Node.h"
#include "HelpFunctions.h"

using namespace Angler;
using namespace Angler::Graphics;
using namespace Angler::Exceptions::Graphics;

GraphicsEngine::GraphicsEngine(Game* parent)
	: mParent(parent), mRunning(false)
{

}

GraphicsEngine::~GraphicsEngine()
{
	for (unsigned int layer = 0; layer < mLayers.size(); layer++)
	{
		delete mLayers.at(layer);
	}
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

GLfloat matrix[16];

void GraphicsEngine::draw(int layer, float originX, float originY, 
					float cropOriginX, float cropOriginY, float cropWidth, float cropHeight,
					float r, float g, float b, float a)
{
	if (mRunning)
	{
		mLayers.at(layer)->draw(originX, originY, cropOriginX, cropOriginY, cropWidth,
			cropHeight, r, g, b, a);
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
void GraphicsEngine::draw(int layer, sf::Vector2f origin, sf::Vector2f cropOrigin,
					sf::Vector2f cropSize, float r, float g, float b, float a)
{
	draw(layer, origin.x, origin.y, cropOrigin.x, cropOrigin.y, cropSize.x, cropSize.y, r, g, b, a);
}

void GraphicsEngine::draw(int layer, float originX, float originY, 
					float r, float g, float b, float a)
{
	draw(layer, originX, originY, 0, 0, 1, 1, r, g, b, a);
}

void GraphicsEngine::draw(int layer, sf::Vector2f origin,
					float r, float g, float b, float a)
{
	draw(layer, origin.x, origin.y, 0, 0, 1, 1, r, g, b, a);
}

void GraphicsEngine::draw(int layer, sf::Vector2f cropOrigin, sf::Vector2f cropSize)
{
	draw(layer, 0, 0, cropOrigin.x, cropOrigin.y, cropSize.x, cropSize.y, 1, 1, 1, 1);
}

void GraphicsEngine::draw(int layer, sf::Vector2f origin, sf::Vector2f cropOrigin,
					sf::Vector2f cropSize)
{
	draw(layer, origin.x, origin.y, cropOrigin.x, cropOrigin.y, cropSize.x, cropSize.y, 
		1, 1, 1, 1);
}

void GraphicsEngine::draw(int layer, sf::Vector2f origin)
{
	draw(layer, origin.x, origin.y);
}

void GraphicsEngine::draw(int layer, float r, float g, float b, 
						 float a)
{
	draw(layer, 0, 0, 0, 0, 1, 1, r, g, b, a);
}

void GraphicsEngine::draw(int layer, float originX, float originY)
{
	draw(layer, originX, originY, 0, 0, 1, 1, 1, 1, 1, 1);
}

void GraphicsEngine::draw(int layer)
{
	draw(layer, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1);
}

void GraphicsEngine::resize(int width, int height)
{
	//Updates the viewport to fit the current size
	glViewport(0, 0, width, height);
}

void GraphicsEngine::mClear()
{
	for (unsigned int layer = 0; layer < mLayers.size(); layer++)
	{
		mLayers.at(layer)->clear();
	}
}

void GraphicsEngine::addLayer(int numElements)
{
	mLayers.push_back(new GraphicsLayer(this, numElements));
}

GraphicsLayer* GraphicsEngine::getLayer(int i)
{
	return mLayers.at(i);
}

void GraphicsEngine::mRender()
{
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	//Iterates over each layer, back to front, and renders all elements
	for (unsigned int layer = 0; layer < mLayers.size(); layer++)
	{
		mLayers.at(layer)->render();
	}

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