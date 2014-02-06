//Version: 0.1.3
//Author: Jakob Pipping
//Contributors:

#ifndef INC_GRAPHICS_H
#define INC_GRAPHICS_H

#ifdef ANGLER_0_1_3

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <glut.h>

namespace Angler
{
	class Game;

	namespace Graphics
	{
		//Graphics Element to store data in the to-draw vectors
		class GraphicElement final
		{
			friend class GraphicsEngine;
		public:
			GraphicElement(GLdouble matrix[16], float originX, float originY,
				float cropOriginX, float cropOriginY, float cropWidth, float cropHeight,
				float r, float g, float b, float a, sf::Texture *texture);
			GraphicElement();

		private:
			GLdouble mMatrix[16];
			float mR, mG, mB, mA;
			float mOriginX, mOriginY;
			float mCropOriginX, mCropOriginY, mCropWidth, mCropHeight;
			sf::Texture *mTexture;
		};

		//Maximum number of elements per layer
		#define MAX_ELEMENTS 512

		class GraphicsEngine final
		{
		public:
			friend class Game;

			GraphicsEngine(Game* parent, int numLayers);
			~GraphicsEngine();

			//Hanldes creating a SFML window and initialize basic functions
			void createWindow(int width, int height, const char* title, bool resizable);

			//Functions to "draw" (push elements onto the vector)
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

			//Has to be called at the beginning of every draw cycle
			void begin();
			//Has to be called at the end of every draw cycle
			void end();

			//Renders to the screen
			void display();

			void close();

			int getWidth(), getHeight();

			//Called from the main loop to resize, not used to force a resize of the screen
			void resize(int width, int height);

			//Wrapper for texture loading (currently using SFML)
			void loadTexture(sf::Texture* texture, const char* fileName);

		private:
			Game* mParent;
			sf::RenderWindow *mWindow;

			int mNumLayers;

			//typedef std::vector<GraphicElement*> GraphicElementVector;
			//GraphicElementVector *mLayers;
			GraphicElement ***mLayers;
			int *mIndx;

			//Clears the layers
			void mClear();

			//Renders the layers
			void mRender();

			//Draws a GraphicElement to the screen
			void mDrawElement(GraphicElement *element);

			bool mRunning;

			sf::Texture *mOldTexture;
		};
	}
}

#else
#error Graphics.h: Wrong Version 0.1.3
#endif

#endif