//Version: 0.1.12
//Author: Jakob Pipping
//Contributors: 

#ifndef ANGLER_0_1_12
#error SoundState.cpp: Wrong Version 0.1.12
#endif

#include "Sound.h"

using namespace Angler::Sound;

SoundState::SoundState(unsigned long id, float volume, float start, float end)
	: mID(id), mVolume(volume), mStart(start), mEnd(end)
{

}

unsigned long SoundState::getID()
{
	return mID;
}

void SoundState::update(SoundElement *s)
{
	s->getSound()->setVolume(mVolume);
	s->mStart = mStart;
	s->mEnd = mEnd;
}