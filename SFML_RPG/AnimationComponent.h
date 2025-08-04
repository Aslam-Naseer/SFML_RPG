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

		void update(sf::Sprite& sprite, const float& dt);
		void reset();
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;

	std::string currentAnimationKey;
	std::map<std::string, Animation*> animations;

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	~AnimationComponent();

	void addAnimation(std::string key, int width, int height, int max_frames, int y_level, float max_time);
	void play(std::string key);

	void update(const float& dt);
};

