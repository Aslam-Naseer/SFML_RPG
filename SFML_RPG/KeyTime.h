#pragma once

class KeyTime
{
private:
	mutable sf::Clock timer;
	sf::Time maxTime;

public:
	KeyTime(float max = .25f);
	virtual ~KeyTime();

	bool consume() const;
	void restart() const;
	bool isReady() const;
};

