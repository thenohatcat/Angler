//Version: 0.1.6
//Author: Jakob Pipping
//Contributors: 

#ifndef ANGLER_0_1_6
#error SoundElement.cpp: Wrong Version 0.1.6
#endif

#include <SFML\Audio.hpp>
#include "Sound.h"

using namespace Angler::Sound;

SoundElement::SoundElement(sf::Sound *s, float start, float end,
			 bool loop)
			 : mSound(s), mStart(start), mEnd(end), mLoop(loop), mIsAlive(true)
{
	mSound->setLoop(mLoop);
	mSound->play();
	mSound->setPlayingOffset(sf::seconds(mStart));
}

bool SoundElement::isAlive()
{
	return mIsAlive;
}

void SoundElement::play()
{
	if (mIsAlive)
		mSound->play();
}

void SoundElement::stop()
{
	if (mIsAlive)
		mSound->stop();
}

void SoundElement::pause()
{
	if (mIsAlive)
		mSound->pause();
}

void SoundElement::update(float time, float deltaTime)
{
	if (mIsAlive)
	{
		if (mSound->getStatus() != sf::Sound::Status::Playing)
		{
			mIsAlive = false;
			return;
		}

		if (mStart >= 0)
		{
			if (mSound->getPlayingOffset().asSeconds() < mStart)
			{
				mSound->setPlayingOffset(sf::seconds(mStart));
			}
		}
		if (mEnd >= 0)
		{
			if (mSound->getPlayingOffset().asSeconds() > mEnd)
			{
				if (mLoop)
				{
					mSound->setPlayingOffset(sf::seconds(mStart));
				}
				else
				{
					mIsAlive = false;
					return;
				}
			}
		}
	}
}

sf::Sound *SoundElement::getSound()
{
	return mSound;
}