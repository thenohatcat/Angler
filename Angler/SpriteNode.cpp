#include "SpriteNode.h"

using namespace Angler;
using namespace Angler::Nodes;

SpriteNode::SpriteNode(unsigned long id, Node *parent, int layer, sf::Texture *tx, 
				float ox, float oy, float cropOriginX, float cropOriginY, 
				float cropWidth, float cropHeight)
				: DrawNode(id, parent, layer, tx, ox, oy), mCropOriginX(cropOriginX),
				mCropOriginY(cropOriginY), mCropWidth(cropWidth), mCropHeight(cropHeight)
{

}

SpriteNode::SpriteNode(unsigned long id, Node *parent, int layer, sf::Texture *tx, 
				sf::Vector2f origo, 
				sf::Vector2f cropOrigin, 
				sf::Vector2f cropSize)
				: DrawNode(id, parent, layer, tx, origo), mCropOriginX(cropOrigin.x),
				mCropOriginY(cropOrigin.y), mCropWidth(cropSize.x), mCropHeight(cropSize.y)
{

}

SpriteNode::SpriteNode(unsigned long id, int layer, sf::Texture *tx, 
				float ox, float oy, float cropOriginX, float cropOriginY, 
				float cropWidth, float cropHeight)
				: DrawNode(id, layer, tx, ox, oy), mCropOriginX(cropOriginX),
				mCropOriginY(cropOriginY), mCropWidth(cropWidth), mCropHeight(cropHeight)
{

}

SpriteNode::SpriteNode(unsigned long id, int layer, sf::Texture *tx, 
				sf::Vector2f origo, 
				sf::Vector2f cropOrigin, 
				sf::Vector2f cropSize)
				: DrawNode(id, layer, tx, origo), mCropOriginX(cropOrigin.x),
				mCropOriginY(cropOrigin.y), mCropWidth(cropSize.x), mCropHeight(cropSize.y)
{

}

void SpriteNode::draw(Game* context, Angler::Graphics::GraphicsEngine* graphics, float time, float deltaTime)
{
	graphics->draw(mLayer, mTX, sf::Vector2f(mOX, mOY), sf::Vector2f(mCropOriginX, mCropOriginY),
		sf::Vector2f(mCropWidth, mCropHeight));

	mDrawChildren(context, graphics, time, deltaTime);
}

void SpriteNode::setCropOrigin(float x, float y)
{
	mCropOriginX = x;
	mCropOriginY = y;
}

void SpriteNode::setCropOrigin(sf::Vector2f origin)
{
	setCropOrigin(origin.x, origin.y);
}

float SpriteNode::getCropOriginX()
{
	return mCropOriginX;
}

float SpriteNode::getCropOriginY()
{
	return mCropOriginY;
}

sf::Vector2f SpriteNode::getCropOrigin()
{
	return sf::Vector2f(getCropOriginX(), getCropOriginY());
}

void SpriteNode::setCropSize(float w, float h)
{
	mCropWidth = w;
	mCropHeight = h;
}

void SpriteNode::setCropSize(sf::Vector2f size)
{
	setCropSize(size.x, size.y);
}

float SpriteNode::getCropWidth()
{
	return mCropWidth;
}

float SpriteNode::getCropHeight()
{
	return mCropHeight;
}

sf::Vector2f SpriteNode::getCropSize()
{
	return sf::Vector2f(getCropWidth(), getCropHeight());
}