#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Spell::Spell()
{
	// Inicjalizacja zmiennych do animacji
	row = 0;
	first = true;
	second = false;
	third = false;

	// Inicjalizacja zmiennych ruchowych
	startingPos = sf::Vector2f(0.0f, 0.0f);
	distance = 0.0f;
	maxDistance = 500.0f;
	speed = 250.0f;
	isMovingRight = true;
}

//---------------------------------------------------------------------------------------

Spell::~Spell()
{
	if (this->texture != nullptr)
	{
		delete this->texture;
		this->texture = nullptr;
	}
}

//---------------------------------------------------------------------------------------

void Spell::setDirection(bool right)
{
	this->isMovingRight = right;
}

//---------------------------------------------------------------------------------------

void Spell::setStartingPos(sf::Vector2f startingPos_)
{
	this->startingPos = startingPos_;
}

//---------------------------------------------------------------------------------------

bool Spell::getDirection()
{
	return this->isMovingRight;
}

//---------------------------------------------------------------------------------------

void Spell::draw(sf::RenderWindow & window)
{
	window.draw(this->getSprite());
}

//---------------------------------------------------------------------------------------

bool Spell::collision(Entity *)
{
	return false;
}

//---------------------------------------------------------------------------------------

void Spell::update(float diff)
{
	if (distance >= maxDistance)
	{
		this->destroy();
	}

	if (first && !second && !third && animation.isForward())
	{
		animation.update(0, diff, true);
	}
	else
	{
		first = false;
		second = true;
	}

	if (!first && second && !third && animation.isForward())
	{
		animation.update(2, diff, true);
	}
	else
	{
		second = false;
		third = true;
	}

	if (!first && !second && third)
	{
		animation.update(2, diff, true);
	}

	sprite.setTextureRect(animation.getIntRect());

	if (isMovingRight)
	{
		sprite.move(sf::Vector2f(this->speed * diff, 0));
	}
	else
	{
		sprite.move(-sf::Vector2f(this->speed * diff, 0));
	}

	distance += this->speed * diff;

}
//---------------------------------------------------------------------------------------

Fireball::Fireball()
{
	texture->loadFromFile(Resources::getFireballTexture());
	sprite.setTexture(*texture);
	sprite.setScale(0.75f, 0.75f);
	animation.setImageCount(sf::Vector2u(5, 5));
	animation.setSize(*texture);
}

//---------------------------------------------------------------------------------------

Fireball::~Fireball()
{
	;
}

//---------------------------------------------------------------------------------------

Frostbolt::Frostbolt()
{
	texture->loadFromFile(Resources::getFireballTexture());
	animation.setImageCount(sf::Vector2u(5, 5));
	animation.setSize(*texture);
}

//---------------------------------------------------------------------------------------

Frostbolt::~Frostbolt()
{
	;
}

//---------------------------------------------------------------------------------------

Shadowbolt::Shadowbolt()
{
	texture->loadFromFile(Resources::getFireballTexture());
	animation.setImageCount(sf::Vector2u(5, 5));
	animation.setSize(*texture);
}

//---------------------------------------------------------------------------------------

Shadowbolt::~Shadowbolt()
{
	;
}

//---------------------------------------------------------------------------------------