#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::Animation::Animation(int width, int height, int max_frames, int y_level, float max_time) :
	width(width), height(height), maxFrames(max_frames), currentFrame(0), 
	yLevel(y_level), maxTime(max_time), curTime(0.f)
{
	currentRect = sf::IntRect({ 0, yLevel * height }, { width, height });
}

AnimationComponent::Animation::~Animation()
{
}

void AnimationComponent::Animation::update(sf::Sprite& sprite, const float& dt)
{
	curTime += dt * maxFrames;

	if (curTime >= maxTime)
	{
		currentFrame++;
		if (currentFrame == maxFrames)
			currentFrame = 0;
	
		currentRect.position.x = currentFrame * width;
		sprite.setTextureRect(currentRect);
		curTime -= maxTime;
	}

	//std::cout << currentFrame << " / " << maxFrames-1 << std::endl;
}

void AnimationComponent::Animation::reset()
{
	currentFrame = 0;
	curTime = 0.f;
}

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet) :
	sprite(sprite), textureSheet(textureSheet)
{
	
	this->sprite.setTexture(this->textureSheet);
	currentAnimationKey = "";
	priorityAnimationKey = "";
}

AnimationComponent::~AnimationComponent()
{
	for (auto& anim : animations)
	{
		delete anim.second;
	}
	animations.clear();
}

void AnimationComponent::addAnimation(std::string key, 
	int width, int height, int max_frames, int y_level, float max_time)
{
	if (animations.find(key) == animations.end())
	{
		animations[key] = new Animation(width, height, max_frames, y_level, max_time);
	}
	else
	{
		std::cerr << "Animation with key '" << key << "' already exists!" << std::endl;
	}
}

void AnimationComponent::play(std::string key, const bool priority)
{
	if (animations.find(key) == animations.end())
	{
		std::cerr << "Animation with key '" << key << "' does not exist!" << std::endl;
		return;
	}

	if(priority && priorityAnimationKey != key)
	{
		priorityAnimationKey = key;
	} 
	
	if(!priority && currentAnimationKey != key)
	{
		currentAnimationKey = key;
		animations[key]->reset();
	}
	
}

void AnimationComponent::update(const float& dt)
{

	if (priorityAnimationKey != "" && animations.find(priorityAnimationKey) != animations.end()) {
		animations[priorityAnimationKey]->update(sprite, dt);
		if (animations[priorityAnimationKey]->isDone())
			priorityAnimationKey = "";
	}

	else if (animations.find(currentAnimationKey) != animations.end())
	{
		animations[currentAnimationKey]->update(sprite, dt);
	}

	else
	{
		std::cout << "Invalid animation key\n";
	}
}