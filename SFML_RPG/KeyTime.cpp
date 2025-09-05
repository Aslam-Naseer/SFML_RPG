#include "stdafx.h"
#include "KeyTime.h"

KeyTime::KeyTime(float max_key_time)
{
	keyTime = 0.f;
	maxKeyTime = max_key_time;
}

KeyTime::~KeyTime()
{
}

const bool KeyTime::isReady() const
{
	if (keyTime >= maxKeyTime)
	{
		keyTime = 0.f;
		return true;
	}

	return false;
}

void KeyTime::update(const float& dt)
{
	if (keyTime < maxKeyTime)
	{
		keyTime += 10.f * dt;
	}
}