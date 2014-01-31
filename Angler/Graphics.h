//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

//Graphics
//Changelog:
//* moved some code from Game::run() to Graphics::begin()
//* moved window handling here from Game
//
//+ added		draw(int, sf::Texture*, float, float, float, float, float, float, float, float, float, float)
//+ added		draw(int, sf::Texture*, sf::Vector2f, sf::Vector2f, sf::Vector2f, float, float, float, float)
//+ added		draw(int, sf::Texture*, sf::Vector2f, float, float, float, float)
//+ added		draw(int, sf::Texture*, sf::Vector2f, sf::Vector2f, sf::Vector2f)
//+ added		draw(int, sf::Texture*, sf::Vector2f)
//+ added		resize(int, int)
//+ added		loadTexture(sf::Texture*, const char*)
//+ added		createWindow(int, int, const char*, sf::Style)
//+ added		int getWidth()
//+ added		int getHeight()

#ifndef INC_GRAPHICS_H
#define INC_GRAPHICS_H

#ifdef ANGLER_0_1_1

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <glut.h>

namespace Angler
{
	class Game;

	namespace Graphics
	{
		class GraphicElement final
		{
			friend class GraphicsEngine;
		public:
			GraphicElement(GLdouble matrix[16], float originX, float originY,
				float cropOriginX, float cropOriginY, float cropWidth, float cropHeight,
				float r, float g, float b, float a, sf::Texture *texture);

		private:
			GLdouble mMatrix[16];
			float mR, mG, mB, mA;
			float mOriginX, mOriginY;
			float mCropOriginX, mCropOriginY, mCropWidth, mCropHeight;
			sf::Texture *mTexture;
		};

		#define MAX_ELEMENTS 1024

		class GraphicsEngine final
		{
		public:
			friend class Game;

			GraphicsEngine(Game* parent, int numLayers);
			~GraphicsEngine();

			void createWindow(int width, int height, const char* title, bool resizable);

			void draw(int layer, sf::Texture* texture, float originX, float originY, 
				float cropOriginX, float cropOriginY, float cropWidth, float cropHeight,
				float r, float g, float b, float a);	
			void draw(int layer, sf::Texture* texture, sf::Vector2f origin, 
				sf::Vector2f cropOrigin, sf::Vector2f cropSize,
				float r, float g, float b, float a);

			void draw(int layer, sf::Texture* texture, float originX, float originY, 
				float r, float g, float b, float a);
			void draw(int layer, sf::Texture* texture, sf::Vector2f origin, 
				float r, float g, float b, float a);

			void draw(int layer, sf::Texture* texture, float r, float g, float b, float a);

			void draw(int layer, sf::Texture* texture, sf::Vector2f cropOrigin, sf::Vector2f cropSize);

			void draw(int layer, sf::Texture* texture, sf::Vector2f origin, 
				sf::Vector2f cropOrigin, sf::Vector2f cropSize);

			void draw(int layer, sf::Texture* texture, float originX, float originY);
			void draw(int layer, sf::Texture* texture, sf::Vector2f origin);
			//draw(int layer, sf::Texture* texture, float cropOriginX, float cropOriginY, 
			//float cropWidth, float cropHeight) doesn't exist as it would conflict
			void draw(int layer, sf::Texture* texture);

			void begin();
			void end();

			void display();

			int getWidth(), getHeight();

			void resize(int width, int height);

			void loadTexture(sf::Texture* texture, const char* fileName);

		private:
			Game* mParent;
			sf::RenderWindow *mWindow;

			int mNumLayers;

			typedef std::vector<GraphicElement*> GraphicElementVector;
			GraphicElementVector *mLayers;

			void mClear();

			void mRender();

			void mDrawElement(GraphicElement *element);

			bool mRunning;
		};
	}
}

#else
#error Graphics.h: Wrong Version 0.1.1
#endif

#endif