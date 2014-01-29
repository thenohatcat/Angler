//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

//Changelog:
//changed parent class to Transformation
//+ added		Scale(sf::Vector2f)
//+ added		Scale(Node*, sf::Vector2f)
//+	added		float getScaleX
//+ added		float getScaleY
//+ added		sf::Vector2f getScale
//+ added		scale(float, float)
//+ added		scale(sf::Vector2f)
//renamed		updateScale to setScale
//+ added		setScale(sf::Vector2f)
//+ added		doTransform()

#ifndef INC_SCALE_H
#define INC_SCALE_H

#ifdef ANGLER_0_1_1

#include "Transformation.h"

#include <SFML\System\Vector2.hpp>

class Scale
	: public Transformation
{
public:
	Scale(float scaleX, float scaleY);
	Scale(sf::Vector2f s);

	Scale(Node *parent, float scaleX, float scaleY);
	Scale(Node *parent, sf::Vector2f s);

	void setScale(float scaleX, float scaleY);
	void setScale(sf::Vector2f s);

	void scale(float scaleX, float scaleY);
	void scale(sf::Vector2f s);

	sf::Vector2f getScale();
	float getScaleX(), getScaleY();

	virtual void draw(Game* context, Graphics* graphics, float time, float deltaTime);

	void doTransform();

private:
	float mScaleX, mScaleY;
};

#else
#error Scale.h: Wrong Version 0.1.1
#endif

#endif