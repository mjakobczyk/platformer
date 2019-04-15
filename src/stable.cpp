#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Stable::Stable() : Entity()
{
	canMove = false;
	collidable = false;
	interactable = false;
	interaction = NONE;
}

//---------------------------------------------------------------------------------------

Stable::~Stable() 
{
	;
};

//---------------------------------------------------------------------------------------

Interaction Stable::getInteraction() 
{ 
	return this->interaction;
}

//---------------------------------------------------------------------------------------

void Stable::draw(sf::RenderWindow & window)
{
	window.draw(this->sprite);
}

//---------------------------------------------------------------------------------------

bool Stable::collision(Entity * stable)
{
	return false;
}

//---------------------------------------------------------------------------------------

bool Stable::isCollidable()
{
	return this->collidable;
}

//---------------------------------------------------------------------------------------

bool Stable::isInteractable()
{
	return this->interactable;
}

//---------------------------------------------------------------------------------------

void Stable::update(float diff)
{
	return;
}

//---------------------------------------------------------------------------------------

Coin::Coin() : Stable()
{
	ID = 20;
	collidable = false;
	interactable = false;
	interaction = BONUS;
	sf::Texture * temp = new sf::Texture;
	if (!temp->loadFromFile(Resources::getCoinTexture()))
		std::cout << "Failed to load Coin texture!" << std::endl;
	setTexture(temp);
	coords = sf::Vector2i(0, 0);
}

//---------------------------------------------------------------------------------------

Coin::~Coin()
{
	;
}

//---------------------------------------------------------------------------------------

bool Coin::collision(Entity *)
{
	std::cout << "Coin collision!" << std::endl;
	return true;
}

//---------------------------------------------------------------------------------------