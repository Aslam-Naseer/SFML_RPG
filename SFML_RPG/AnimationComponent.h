#pragma once

#include <iostream>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class AnimationComponent
{
private:

	class Animation 
	{
	public:
		float curTime;
		float maxTime;

		int width;
		int height;
		int currentFrame;
		int maxFrames;
		int yLevel;

		sf::IntRect currentRect;

		Animation(int width, int height, int max_frames, int y_level, float max_time);
		~Animation();

		bool isDone() const { return currentFrame == maxFrames - 1; }

		void update(sf::Sprite& sprite, const float& dt);
		void reset();
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::string currentAnimationKey;
	std::string priorityAnimationKey;
	std::map<std::string, Animation*> animations;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	~AnimationComponent();

	bool isPriority(std::string key) const { return priorityAnimationKey == key; }

	void addAnimation(std::string key, int width, int height, int max_frames, int y_level, float max_time);
	void play(std::string key, const bool priority = false);

	void update(const float& dt);
};

