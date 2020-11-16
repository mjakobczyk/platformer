#include "../include/basic.h"

#include <cstdlib>

//---------------------------------------------------------------------------------------

Character::Character() : Moveable(), name("unknown"), health(10), mana(10), animation()
{
	tempDelta = 0.0;
	offset = 0.0f;
	gravity = 5.0f;
	moveSpeed = 100.0f;
	jumpSpeed = 300.0f;
	groundHeight = 620.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);

	faceRight = true;
	isJumping = false;
	isFalling = false;
	canMoveRight = true;
	canMoveLeft = true;
	canJump = true;
	canFall = false;
	isColliding = false;
	lastDirection = UNKNOWN;

	row = 1;
	if (!(*texture).loadFromFile(Resources::getWarlockTexture()))
	{
		std::cerr << "Texture: " << Resources::getWarlockTexture() << "could not be loaded" << std::endl;
	}
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(50.0f, 50.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
	pendingSpell = false;
}

//---------------------------------------------------------------------------------------

Character::Character(sf::Texture *texture_) : Moveable(), name("unknown"), health(10), mana(10), animation(texture_)
{
	tempDelta = 0.0;
	offset = 0.0f;
	gravity = 5.0f;
	moveSpeed = 100.0f;
	jumpSpeed = 300.0f;
	groundHeight = 620.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);

	faceRight = false;
	isJumping = false;
	isFalling = false;
	canMoveRight = true;
	canMoveLeft = true;
	canJump = true;
	canFall = false;
	isColliding = false;
	lastDirection = UNKNOWN;

	row = 1;
	texture = texture_;
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(50.0f, 50.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
	pendingSpell = false;
}

//---------------------------------------------------------------------------------------

Character::Character(sf::Vector2u imageCount_, float switchTime_) : Moveable(), name("unknown"), health(10), mana(10), animation(imageCount_, switchTime_)
{
	tempDelta = 0.0;
	offset = 0.0f;
	gravity = 5.0f;
	moveSpeed = 100.0f;
	jumpSpeed = 300.0f;
	groundHeight = 620.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);

	faceRight = false;
	isJumping = false;
	isFalling = false;
	canMoveRight = true;
	canMoveLeft = true;
	canJump = true;
	canFall = false;
	isColliding = false;
	lastDirection = UNKNOWN;

	row = 1;
	if (!(*texture).loadFromFile(Resources::getWarlockTexture()))
	{
		std::cerr << "Texture: " << Resources::getWarlockTexture() << "could not be loaded" << std::endl;
	}
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(50.0f, 50.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
	pendingSpell = false;
};

//---------------------------------------------------------------------------------------

Character::Character(sf::Texture *texture_, sf::Vector2u imageCount_, float switchTime_) : Moveable(), name("unknown"), health(10), mana(10), animation(texture_, imageCount_, switchTime_)
{
	tempDelta = 0.0;
	offset = 0.0f;
	gravity = 5.0f;
	moveSpeed = 100.0f;
	jumpSpeed = 300.0f;
	groundHeight = 620.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);

	faceRight = false;
	isJumping = false;
	isFalling = false;
	canMoveRight = true;
	canMoveLeft = true;
	canJump = true;
	canFall = false;
	isColliding = false;
	lastDirection = UNKNOWN;

	row = 1;
	if (!(*texture).loadFromFile(Resources::getWarlockTexture()))
	{
		std::cerr << "Texture: " << Resources::getWarlockTexture() << "could not be loaded" << std::endl;
	}
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(50.0f, 50.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
	pendingSpell = false;
};

//---------------------------------------------------------------------------------------

Character::~Character()
{
	if (this->texture != nullptr)
	{
		delete this->texture;
		this->texture = nullptr;
	}
}

//---------------------------------------------------------------------------------------

int Character::getHealth()
{
	return this->health;
}

//---------------------------------------------------------------------------------------

Direction Character::getLastDirection()
{
	return this->lastDirection;
}

//---------------------------------------------------------------------------------------

sf::Vector2f Character::getLastMovement()
{
	return this->lastMovement;
}

//---------------------------------------------------------------------------------------

void Character::setX(float x_)
{
	this->coords.x = x_;
}

//---------------------------------------------------------------------------------------

void Character::setY(float y_)
{
	this->coords.y = y_;
}

//---------------------------------------------------------------------------------------

void Character::setName(const std::string &name_)
{
	this->name = name_;
}

//---------------------------------------------------------------------------------------

void Character::setHealth(int health_)
{
	this->health = health_;
}

//---------------------------------------------------------------------------------------

void Character::setMana(int mana_)
{
	this->mana = mana_;
}

//---------------------------------------------------------------------------------------


void Character::setDirection(bool goRight)
{
	this->faceRight = goRight;
}

//---------------------------------------------------------------------------------------

void Character::setCollisionState(bool collision)
{
	this->isColliding = collision;
}

//---------------------------------------------------------------------------------------

bool Character::isFacingRight()
{
	return this->faceRight;
}

//---------------------------------------------------------------------------------------

bool Character::isSpellPending()
{
	return this->pendingSpell;
}

//---------------------------------------------------------------------------------------

void Character::move(sf::Vector2f newMovement)
{
	this->sprite.move(newMovement);
}

//---------------------------------------------------------------------------------------

void Character::slow(float delta)
{
	if (!debuffActive)
	{
		this->moveSpeed = 25.0f;
		this->tempDelta = delta;
		this->debuffActive = true;
	}
}

//---------------------------------------------------------------------------------------

void Character::hurt(float delta)
{
	if (!debuffActive)
	{
		this->health--;
		this->tempDelta = delta;
		this->debuffActive = true;
	}
}

//---------------------------------------------------------------------------------------

void Character::update(float diff)
{
	movement = sf::Vector2f(0.0f, 0.0f);

	// Moving left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (canMoveLeft)
		{
			movement.x -= moveSpeed * diff;
			row = 1;
			lastDirection = LEFT;
			faceRight = false;
		}
	}

	// Moving right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (canMoveRight)
		{
			movement.x += moveSpeed * diff;
			row = 2;
			lastDirection = RIGHT;
			faceRight = true;
		}
	}

	// Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (canJump)
		{
			if (isJumping == false && isFalling == false)
			{
				isJumping = true;
				isFalling = false;
				offset = jumpSpeed;
				lastDirection = UP;
			}
		}
	}

	if (isJumping == true)
	{
		offset -= gravity;
		movement.y -= offset * diff;
		// Je�eli posta� osi�gnie maksymaln� d�ugo�� skoku
		if (offset <= 0)
		{
			isJumping = false;
			isFalling = true;
			offset = 0.0f;
		}
		lastDirection = UP;
	}

	if (isFalling == true)
	{
		offset += gravity;
		movement.y += offset * diff;
		lastDirection = DOWN;

		if (this->getSprite().getPosition().y > groundHeight) // + this->getSprite().getGlobalBounds().height
		{
			isJumping = false;
			isFalling = false;
			offset = 0.0f;
			movement.y = 0;
			lastDirection = RIGHT;
		}
	}

	if (debuffActive == true)
	{
		if (clock.getElapsedTime().asSeconds() > tempDelta)
		{
			moveSpeed = 100.0f;
			tempDelta = 0.0;
			clock.restart().asSeconds();
			debuffActive = false;
		}
	}

	if (movement.x == 0.0f && movement.y == 0.0f)
	{
		return;
	}
	else
	{
		animation.update(row, diff, faceRight);
		sprite.setTextureRect(animation.getIntRect());
		sprite.move(movement);
		lastMovement = movement;
		return;
	}
}

//---------------------------------------------------------------------------------------

void Character::draw(sf::RenderWindow &window_)
{
	window_.draw(sprite);
}

//---------------------------------------------------------------------------------------

bool Character::collision(Entity *entity)
{
	if (typeid(*entity) == typeid(Tile))
	{
		switch (entity->getID())
		{
		case TileType::STONE_1:
		case TileType::BRICK_1:
		case TileType::BRICK_2:
		{
			isColliding = true;

			// Collision from right
			if (this->getLastMovement().x > 0)
			{
				this->move(sf::Vector2f(-std::abs(this->getLastMovement().x), 0));

				if (this->getSprite().getPosition().y + this->getSprite().getGlobalBounds().height < groundHeight && isJumping == false)
				{
					this->isFalling = true;
				}
			}

			// Collision from left
			else if (this->getLastMovement().x < 0)
			{
				this->move(sf::Vector2f(std::abs(this->getLastMovement().x), 0));

				if (this->getSprite().getPosition().y + this->getSprite().getGlobalBounds().height < groundHeight && isJumping == false)
				{
					this->isFalling = true;
				}
			}

			// Collision from down
			if (this->getLastMovement().y < 0)
			{
				this->isJumping = false;
				this->isFalling = true;
				this->move(sf::Vector2f(0, std::abs(this->getLastMovement().y)));
			}

			// Kolizja from up
			else if (this->getLastMovement().y > 0)
			{
				this->isJumping = false;
				this->isFalling = false;
				this->move(sf::Vector2f(0, -std::abs(this->getLastMovement().y)));
				this->movement.y = 0;
			}

			break;
		}

		case TileType::LAVA_1:
		case TileType::LAVA_2:
		{
			this->hurt(3);
		}
		case TileType::WATER_1:
		{
			this->slow(1);
		}
		default:
		{
			break;
		}
		}
	}
	else if (typeid(*entity) == typeid(Coin))
	{
		// TODO: add points when interacting with coin
	}
	else if (typeid(*entity) == typeid(Enemy))
	{
		this->hurt(3);
	}

	return true;
}

//---------------------------------------------------------------------------------------