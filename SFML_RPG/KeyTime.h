#pragma once

class KeyTime
{
private:
	mutable float keyTime;
	float maxKeyTime;

public:
		KeyTime(float max_key_time = 1.f);
		virtual ~KeyTime();

		const bool isReady() const;
		void update(const float& dt);
};

