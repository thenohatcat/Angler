//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

//Changelog:
//changed parent class to Transformation
//+ added		Translation(sf::Vector2f)
//+ added		Translation(Node*, sf::Vector2f)
//+ added		sf::Vector2f getTranslation();
//+ added		float getTranslationX()
//+ added		float getTranslationY()
//+ added		void translate(float, float)
//+ added		void translate(sf::Vector2f)
//renamed		updateTranslation to setTranslation
//+ added		setTranslation(sf::Vector2f)
//+ added		doTransform()

#ifndef INC_TRANSLATION_H
#define INC_TRANLSATION_H

#ifdef ANGLER_0_1_1

#include "Transformation.h"

#include <SFML\System\Vector2.hpp>

class Translation
	: public Transformation
{
public:
	Translation(float x, float y);
	Translation(sf::Vector2f translation);

	Translation(Node *parent, float x, float y);
	Translation(Node *parent, sf::Vector2f translation);

	void setTranslation(float x, float y);
	void setTranslation(sf::Vector2f translation);

	void translate(float x, float y);
	void translate(sf::Vector2f translation);

	sf::Vector2f getTranslation();
	float getTranslationX(), getTranslationY();

	virtual void draw(Game* context, Graphics* graphics, float time, float deltaTime);

	void doTransform();

private:
	float mX, mY;
};

#else
#error Transformation.h: Wrong Version 0.1.1
#endif

#endif