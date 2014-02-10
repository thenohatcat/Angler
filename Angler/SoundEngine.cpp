//Version: 0.1.4
//Author: Oskar Engblad
//Contributors:

#ifndef ANGLER_0_1_4
#error SoundEngine.cpp: Wrong Version 0.1.4
#endif

#include "Sound.h"

SoundEngine::SoundEngine()
{
}

SoundEngine::~SoundEngine()
{
}

void Sound::playSound(sf::Sound *s)
{
	s.play();
}

void Sound::pauseSound(sf::Sound *s)
{
	s.pause();
}

void Sound::stopSound(sf::Sound *s)
{
	s.stop();
}

float Sound::getVolume(sf::Sound *s)
{
	float x = s.getVolume();
}

float Sound::setVolume(sf::Sound *s, float x)
{
	s.setVolume(x);
}

int Sound::getStatus(sf::Sound *s)
{
	int x = s.getStatus();
	return x;
}

float Sound::getPosition(sf::Sound *s)
{
	float x = s.getPlayingOffset().asSeconds();
	return x;
}

float Sound::setPosition(sf::Sound *s, float x)
{
	s.setPlayingOffset(x.asSeconds());
}

void Sound::crossfade(sf::Sound *s1, float t, sf::Sound *s2, float v)
{
	if(s1.getPlayingOffset().asSeconds()>=t && s1.getVolume() > 0)
	{
		//updated every second/millisecond of track
		//Decrement Volume 
		s1.setVolume(s1.getVolume=-v);
		//Increment Volume 
		//Sum total s1+s2 = 100
		s2.setVolume(s2.getVolume=+v);
	}
}