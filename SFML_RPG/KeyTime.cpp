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

bool KeyTime::consume() const
{
	if (timer.getElapsedTime() >= maxTime)
	{
		timer.restart();
		return true;
	}

	return false;
}

bool KeyTime::isReady() const
{
	return timer.getElapsedTime() >= maxTime;
}

void KeyTime::restart() const
{
	timer.restart();
}
