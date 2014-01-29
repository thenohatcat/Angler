#ifndef INC_GAME_H
#define INC_GAME_H

#include "Graphics.h"
#include "Node.h"

#include "Keyboard.h"
#include "Mouse.h"

class Game
{
	friend class Graphics;

public:
	Game();
	~Game();

	void init();

	void loadContent();

	void run();

	KeyboardState getKeyboardState();
	MouseState getMouseState();

protected:
	Graphics* mGraphics;
	Node* mSceneRoot;
	Keyboard* mKeyboard;
	Mouse* mMouse;

	virtual void mDraw(float time, float deltaTime) = 0;
	virtual void mUpdate(float time, float deltaTime) = 0;

	virtual void mLoadContent() = 0;

	virtual void mInnerInit() = 0;

	float mGetTime();
	sf::Clock mGameClock;

	int mHeight;
	int mWidth;

	sf::RenderWindow *mWindow;

	const char *mTitle;
	int mNumLayers;
	bool mFocused;

private:
	void mResize(int width, int height);
};

#endif