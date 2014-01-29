#ifndef INC_GRAPHICS_H
#define INC_GRAPHICS_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <glut.h>

class Game;

class GraphicElement final
{
	friend class Graphics;
public:
	GraphicElement(GLdouble matrix[16], float originX, float originY, 
		float r, float g, float b, float a, sf::Texture *texture);

private:
	GLdouble mMatrix[16];
	float mR, mG, mB, mA;
	float mOriginX, mOriginY;
	sf::Texture *mTexture;
};

#define MAX_ELEMENTS 512

class Graphics final
{
public:

	Graphics(Game *parent);
	~Graphics();

	void draw(int layer, sf::Texture *texture, float originX, float originY, 
		float r, float g, float b, float a);
	void draw(int layer, sf::Texture *texture, float r, float g, float b, float a);
	void draw(int layer, sf::Texture *texture, float originX, float originY);
	void draw(int layer, sf::Texture *texture);

	void begin();
	void end();

	typedef std::vector<GraphicElement*> GraphicElementVector;

private:
	Game* mParent;

	GraphicElementVector *mLayers;

	void mClear();

	void mRender();

	void mDrawElement(GraphicElement *element);

	bool mRunning;
};

#endif