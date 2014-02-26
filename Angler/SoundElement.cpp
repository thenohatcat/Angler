//Version: 0.1.9
//Author: Jakob Pipping
//Contributors: 

#ifndef ANGLER_0_1_9
#error SoundElement.cpp: Wrong Version 0.1.9
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
	if (mStart < 0)
		mStart = 0;
	if (mEnd < 0)
		mEnd = mSound->getBuffer()->getDuration().asSeconds();

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

		if (mSound->getPlayingOffset().asSeconds() < mStart)
		{
			mSound->setPlayingOffset(sf::seconds(mStart));
		}
		if (mSound->getPlayingOffset().asSeconds() >= mEnd)
		{
			if (mLoop)
			{
				mSound->setPlayingOffset(sf::seconds(mStart));
			}
			else
			{
				mSound->stop();
				mIsAlive = false;
				return;
			}
		}
	}
}

sf::Sound *SoundElement::getSound()
{
	return mSound;
}