#pragma once

class KeyTime
{
private:
	mutable sf::Clock timer;
	sf::Time maxTime;

public:
		KeyTime(float max = .25f);
		virtual ~KeyTime();

		const bool isReady() const;
		void restart();
};

