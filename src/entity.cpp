#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Entity::Entity()
{
	ID = -1;
	dead = false;
	canMove = false;
	texture = new sf::Texture;
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(0.0f, 0.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
	coords = sf::Vector2i(0, 0);
	coordsFlt = sf::Vector2f(0.0f, 0.0f);
}

//---------------------------------------------------------------------------------------

Entity::~Entity()
{
	;
}

//---------------------------------------------------------------------------------------

bool Entity::isStable()
{
	if (this->canMove) return false;
	else return true;
}

//---------------------------------------------------------------------------------------

bool Entity::isMoveable()
{
	if (this->canMove)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------------------------------------

bool Entity::isDead()
{
	return this->dead;
}

//---------------------------------------------------------------------------------------

bool Entity::destroy()
{
	if (!this->dead)
	{
		this->dead = true;
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------------------------------------

void Entity::setTexture(sf::Texture * newTexture)
{
	if (texture != nullptr) delete this->texture;
	texture = new sf::Texture(*newTexture);
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(0.0f, 0.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
}

//---------------------------------------------------------------------------------------

void Entity::setPosition(sf::Vector2f newPosition)
{
	if (newPosition.x >= 0.0f && newPosition.y >= 0.0f)
	{
		this->sprite.setPosition(newPosition);
	}
}

//---------------------------------------------------------------------------------------

void Entity::setCoords(sf::Vector2i newCoords)
{
	this->coords = newCoords;
}

//---------------------------------------------------------------------------------------

sf::Vector2i Entity::getCoords() // Zwraca pozycj� jednostki w wersji kafelkowanej
{
	return sf::Vector2i(this->coords);
}

//---------------------------------------------------------------------------------------

sf::Vector2f Entity::getPosition()
{
	return sf::Vector2f(this->getSprite().getPosition().x, this->getSprite().getPosition().y);
}

//---------------------------------------------------------------------------------------

bool Entity::checkCollision(Entity * entity)
{
	return (this->getSprite().getGlobalBounds().intersects(entity->getSprite().getGlobalBounds()));
}

//---------------------------------------------------------------------------------------
