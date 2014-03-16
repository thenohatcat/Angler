//Version: 0.1.11
//Author: Jakob Pipping
//Contributors: 

#ifndef ANGLER_0_1_11
#error SoundEngine.cpp: Wrong Version 0.1.11
#endif

#include <SFML\Audio.hpp>
#include "Game.h"
#include "Sound.h"

using namespace Angler;
using namespace Angler::Sound;

SoundEngine::SoundEngine(Game *parent)
	: mParent(parent)
{
}

bool SoundEngine::playSound(sf::Sound *s, bool hard, float start, float end, bool loop)
{
	//Isn't in list
	if (mGetIndex(s) == mSoundElements.end())
	{
		mSoundElements.push_back(new SoundElement(s, start, end, loop));
		return true;
	}
	else
	{
		return false;
	}
}

void SoundEngine::pauseSound(sf::Sound *s)
{
	s->pause();
}

void SoundEngine::stopSound(sf::Sound *s)
{
	s->stop();
}

float SoundEngine::getVolume(sf::Sound *s)
{
	float x = s->getVolume();
	return x;
}

void SoundEngine::setVolume(sf::Sound *s, float x)
{
	s->setVolume(x);
}

int SoundEngine::getStatus(sf::Sound *s)
{
	int x = s->getStatus();
	return x;
}

float SoundEngine::getPosition(sf::Sound *s)
{
	float x = s->getPlayingOffset().asSeconds();
	return x;
}

void SoundEngine::setPosition(sf::Sound *s, float x)
{
	s->setPlayingOffset(sf::Time(sf::seconds(x)));
}

void SoundEngine::crossfade(sf::Sound *s1, float t, sf::Sound *s2, float v)
{
	if(s1->getPlayingOffset().asSeconds()>=t && s1->getVolume() > 0)
	{
		//updated every second/millisecond of track
		//Decrement Volume 
		s1->setVolume(s1->getVolume() - v);
		//Increment Volume 
		//Sum total s1+s2 = 100
		s2->setVolume(s2->getVolume() + v);
	}
}

void SoundEngine::update(float time, float deltaTime)
{
	for (std::list<SoundElement*>::iterator i = mSoundElements.begin(); i != mSoundElements.end(); i++)
	{
		(*i)->update(time, deltaTime);
	}

	for (std::list<SoundElement*>::iterator i = mSoundElements.begin(); i != mSoundElements.end(); )
	{
		if (!(*i)->isAlive())
		{
			SoundElement *s = *i;
			i = mSoundElements.erase(i);
			delete s;
		}
		else
		{
			i++;
		}
	}
}

std::list<SoundElement*>::iterator SoundEngine::mGetIndex(sf::Sound *s)
{
	for (std::list<SoundElement*>::iterator i = mSoundElements.begin(); i != mSoundElements.end(); i++)
	{
		if ((*i)->getSound() == s)
			return i;
	}
	return mSoundElements.end();
}