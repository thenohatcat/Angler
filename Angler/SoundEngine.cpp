//Version: 0.1.6
//Author: Oskar Engblad
//Contributors: Jakob Pipping

#ifndef ANGLER_0_1_6
#error SoundEngine.cpp: Wrong Version 0.1.6
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

void SoundEngine::playSound(sf::Sound *s)
{
	s->play();
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
