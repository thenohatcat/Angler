//Version: 0.1.12
//Author: Jakob Pipping
//Contributors: 

#ifndef ANGLER_0_1_12
#error SoundEngine.cpp: Wrong Version 0.1.12
#endif

#include <fstream>
#include <sstream>

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
	if (mGetElementIndex(s) == mSoundElements.end())
	{
		mSoundElements.push_back(new SoundElement(s, start, end, loop));
		return true;
	}
	else
	{
		return false;
	}
}

bool SoundEngine::playSound(sf::Sound *s, bool hard, unsigned long id, bool loop)
{
	SoundState *st = (*mGetStateIndex(id));
	setVolume(s, st->mVolume);
	return playSound(s, hard, st->mStart, st->mEnd, loop);
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

//void SoundEngine::crossfade(sf::Sound *s1, float t, sf::Sound *s2, float v)
//{
//	if(s1->getPlayingOffset().asSeconds()>=t && s1->getVolume() > 0)
//	{
//		//updated every second/millisecond of track
//		//Decrement Volume 
//		s1->setVolume(s1->getVolume() - v);
//		//Increment Volume 
//		//Sum total s1+s2 = 100
//		s2->setVolume(s2->getVolume() + v);
//	}
//}

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

void SoundEngine::addSoundState(unsigned long id, float volume, float start, float end)
{
	mSoundStates.push_back(new SoundState(id, volume, start, end));
}

void SoundEngine::updateState(sf::Sound *s, unsigned long id)
{
	std::list<SoundElement*>::iterator se = mGetElementIndex(s);
	std::list<SoundState*>::iterator ss = mGetStateIndex(id);
	if (se != mSoundElements.end() && ss != mSoundStates.end())
	{
		(*ss)->update(*se);
	}
}

std::list<SoundElement*>::iterator SoundEngine::mGetElementIndex(sf::Sound *s)
{
	for (std::list<SoundElement*>::iterator i = mSoundElements.begin(); i != mSoundElements.end(); i++)
	{
		if ((*i)->getSound() == s)
			return i;
	}
	return mSoundElements.end();
}

std::list<SoundState*>::iterator SoundEngine::mGetStateIndex(unsigned long id)
{
	for (std::list<SoundState*>::iterator i = mSoundStates.begin(); i != mSoundStates.end(); i++)
	{
		if ((*i)->getID() == id)
			return i;
	}
	return mSoundStates.end();
}

void SoundEngine::loadStates(std::string file)
{
	std::string content = "";
	std::ifstream fileS(file);

	if (fileS.is_open())
	{
		std::string row = "";
		while (!fileS.eof())
		{
			char c;
			c = fileS.get();

			if (c == '\n' || c == '\r')
			{
				size_t t = row.find('#');
				size_t s = std::string::npos;
				if (row.find('#') == std::string::npos && row.size() > 0)
					content += row + '\n';
				row = "";
			}
			else
			{
				row += c;
			}
		}
	}

	std::stringstream stream(content);	

	unsigned long id;
	char dl;
	float volume;
	float start;
	float end;
	while (!stream.eof())
	{
		stream >> std::hex >> id;
		stream >> dl;
		stream >> volume;
		stream >> start;
		stream >> end;

		addSoundState(id, volume, start, end);
	}
}