//Version: 0.1.12
//Author: Jakob Pipping
//Contributors:

#ifndef INC_GRAPHICS_H
#define INC_GRAPHICS_H

#ifdef ANGLER_0_1_12

#include <SFML\OpenGL.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <vector>

namespace Angler
{
	class Game;

	namespace Graphics
	{
		class GraphicsEngine;

		//Maximum number of elements per layer
		#define MAX_ELEMENTS 512

		class GraphicsLayer final
		{
		public:
			GraphicsLayer(GraphicsEngine *owner, int numElements, 
				int cropX, int cropY, int cropW, int cropH);

			void render();

			void draw(float originX, float originY, 
				float cropOriginX, float cropOriginY, float cropWidth, float cropHeight,
				float r, float g, float b, float a);

			void setTexture(sf::Texture *tx);

			void clear();

			void setCrop(int x, int y, int w, int h);

		private:
			GLfloat *mBuffVertex;
			GLfloat *mBuffTexCord;
			GLfloat *mBUffColor;

			GLfloat mMatrix[16];

			sf::Texture *mTexture;

			float mTextureAR;

			int mOldCropX, mOldCropY, mOldCropW, mOldCropH;

			int mNumElements;

			int mIndx;

			int mCropX, mCropY, mCropW, mCropH;

			GraphicsEngine *mOwner;
		};

		class GraphicsEngine final
		{
		public:
			friend class Game;

			GraphicsEngine(Game* parent);
			~GraphicsEngine();

			//Hanldes creating a SFML window and initialize basic functions
			void createWindow(int width, int height, const char* title, bool resizable);

			void crop(int layer, float x, float y, float w, float h);
			void resetCrop(int layer);

			void draw(int layer, float originX, float originY, 
				float cropOriginX, float cropOriginY, float cropWidth, float cropHeight,
				float r, float g, float b, float a);	
			void draw(int layer, sf::Vector2f origin, 
				sf::Vector2f cropOrigin, sf::Vector2f cropSize,
				float r, float g, float b, float a);

			void draw(int layer, float originX, float originY, 
				float r, float g, float b, float a);
			void draw(int layer, sf::Vector2f origin, 
				float r, float g, float b, float a);

			void draw(int layer, float r, float g, float b, float a);

			void draw(int layer, sf::Vector2f cropOrigin, sf::Vector2f cropSize);

			void draw(int layer, sf::Vector2f origin, 
				sf::Vector2f cropOrigin, sf::Vector2f cropSize);

			void draw(int layer, float originX, float originY);
			void draw(int layer, sf::Vector2f origin);
			//draw(int layer, float cropOriginX, float cropOriginY, 
			//float cropWidth, float cropHeight) doesn't exist as it would conflict
			void draw(int layer);

			//Has to be called at the beginning of every draw cycle
			void begin();
			//Has to be called at the end of every draw cycle
			void end();

			void addLayer(int numElements);
			GraphicsLayer* getLayer(int i);

			void clearLayers();
			void removeLayer(int layer);

			//Renders to the screen
			void display();

			void close();

			int getWidth(), getHeight();

			//Called from the main loop to resize, not used to force a resize of the screen
			void resize(int width, int height);

			//Wrapper for texture loading (currently using SFML)
			void loadTexture(sf::Texture* texture, const char* fileName);

			void setCursorVisible(bool visible);

		private:
			Game* mParent;
			sf::RenderWindow *mWindow;

			typedef std::vector<GraphicsLayer*> LayerVector;
			LayerVector mLayers;

			int mCropX, mCropY, mCropW, mCropH;

			//Clears the layers
			void mClear();

			//Renders the layers
			void mRender();

			bool mRunning;
		};
	}
}

#else
#error Graphics.h: Wrong Version 0.1.12
#endif

#endif