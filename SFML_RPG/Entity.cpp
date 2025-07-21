#include "Entity.h"

// Constructors and Destructors

Entity::Entity()
{
	shape.setSize(sf::Vector2f(50.f, 50.f));
	shape.setFillColor(sf::Color::Green);
	speed = 350.f; // Default speed
}

Entity::~Entity()
{
}

// Functions

void Entity::move(const float& dt, int dir_x, int dir_y)
{
	shape.move({ dir_x * speed * dt, dir_y * speed * dt });
}

void Entity::update(const float& dt)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
	{
		move(dt, -1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
	{
		move(dt, 1, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) 
			{
		move(dt, 0, -1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
	{
		move(dt, 0, 1);
	}
}

void Entity::render(sf::RenderTarget* target)
{
	if (target)
	{
		target->draw(shape);
	}
}
