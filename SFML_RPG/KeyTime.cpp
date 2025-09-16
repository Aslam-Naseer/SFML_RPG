#include "stdafx.h"
#include "KeyTime.h"

KeyTime::KeyTime(float max)
{
	maxTime = sf::seconds(max);
	timer.restart();
}

KeyTime::~KeyTime()
{
}

const bool KeyTime::isReady() const
{
	if (timer.getElapsedTime() >= maxTime)
	{
		timer.restart();
		return true;
	}

	return false;
}

void KeyTime::restart()
{
	timer.restart();
}
