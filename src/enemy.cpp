#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Enemy::Enemy() : Character()
{
	// Inicjalizacja zmiennych dotycz�cych ruchu
	gravity = 0.0f;
	moveSpeed = 25.0f;
	jumpSpeed = 0.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);
	startPos = sf::Vector2f(0.0f, 0.0f);
	endPos = sf::Vector2f(0.0f, 0.0f);
	backPos = sf::Vector2f(0.0f, 0.0f);

	// Ustawienie flag dotycz�cych ruchu
	canJump = false;

	totalTime = 0.0f;
	switchTime = 0.1f;
	imageNumber = 1;
}

//---------------------------------------------------------------------------------------

Enemy::Enemy(sf::Texture * texture_, sf::Vector2u imageCount_, float switchTime_) :
	Character(texture_, imageCount_, switchTime_)
{
	// Inicjalizacja zmiennych dotycz�cych ruchu
	gravity = 0.0f;
	moveSpeed = 25.0f;
	jumpSpeed = 0.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);
	startPos = sf::Vector2f(0.0f, 0.0f);
	endPos = sf::Vector2f(0.0f, 0.0f);
	backPos = sf::Vector2f(0.0f, 0.0f);

	// Ustawienie flag dotycz�cych ruchu
	canJump = false;

	totalTime = 0.0f;
	switchTime = 0.1f;
	imageNumber = 1;
}

//---------------------------------------------------------------------------------------

Enemy::Enemy(sf::Vector2u imageCount_, float switchTime_) :
	Character(imageCount_, switchTime_)
{
	// Inicjalizacja zmiennych dotycz�cych ruchu
	gravity = 0.0f;
	moveSpeed = 25.0f;
	jumpSpeed = 0.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);
	startPos = sf::Vector2f(0.0f, 0.0f);
	endPos = sf::Vector2f(0.0f, 0.0f);
	backPos = sf::Vector2f(0.0f, 0.0f);

	// Ustawienie flag dotycz�cych ruchu
	canJump = false;

	totalTime = 0.0f;
	switchTime = 0.1f;
	imageNumber = 1;
}

//---------------------------------------------------------------------------------------

Enemy::~Enemy()
{
	if (this->texture != nullptr)
	{
		delete this->texture;
		this->texture = nullptr;
	}
}

//---------------------------------------------------------------------------------------

void Enemy::setStartPos(sf::Vector2f startPos_)
{
	this->startPos = startPos_;
}

//---------------------------------------------------------------------------------------

void Enemy::setEndPos(sf::Vector2f endPos_)
{
	this->endPos = endPos_;
}

//---------------------------------------------------------------------------------------

void Enemy::setBackPos(sf::Vector2f backPos_)
{
	this->backPos = backPos_;
}

//---------------------------------------------------------------------------------------

void Enemy::setSize(sf::Vector2f scale)
{
	this->sprite.setScale(scale);
}

//---------------------------------------------------------------------------------------

void Enemy::setDirection(bool direction)
{
	this->faceRight = direction;
}

//---------------------------------------------------------------------------------------

void Enemy::setMoveSpeed(float moveSpeed_)
{
	this->moveSpeed = moveSpeed_;
}

//---------------------------------------------------------------------------------------

sf::Vector2f Enemy::getStartPos()
{
	return this->startPos;
}

//---------------------------------------------------------------------------------------

sf::Vector2f Enemy::getEndPos()
{
	return this->endPos;
}

//---------------------------------------------------------------------------------------

sf::Vector2f Enemy::getBackPos()
{
	return this->backPos;
}

//---------------------------------------------------------------------------------------

Zombie::Zombie() :
	Enemy()
{
	// Ustawienie rz�du aniamcji, tekstury i sprite'a
	sf::Texture * texture = new sf::Texture;
	if (!(*texture).loadFromFile("Grafiki/zombie.png"))
		std::cout << "Blad wczytywania tekstury!" << std::endl;

	animation.setImageCount(sf::Vector2u(9, 1));
	animation.setSize(*texture);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 46, 84));
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(500.0f, 500.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
}

//---------------------------------------------------------------------------------------

Zombie::Zombie(sf::Vector2u imageCount_, float switchTime_) :
	Enemy(imageCount_, switchTime_)
{
	// Ustawienie rz�du aniamcji, tekstury i sprite'a
	if (!(*texture).loadFromFile("Grafiki/zombie.png"))
		std::cout << "Blad wczytywania tekstury!" << std::endl;
	animation.setSize(*texture);
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(500.0f, 500.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
}

//---------------------------------------------------------------------------------------

Zombie::Zombie(sf::Texture * texture_, sf::Vector2u imageCount_, float switchTime_) :
	Enemy(texture_, imageCount_, switchTime_)
{
	// Ustawienie rz�du aniamcji, tekstury i sprite'a
	animation.setSize(*texture);
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(500.0f, 500.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
}

//---------------------------------------------------------------------------------------

Zombie::~Zombie()
{
	;
}

//---------------------------------------------------------------------------------------

void Zombie::update(float diff)
{
	//sprite.setScale(0.5f, 0.5f);

	movement = sf::Vector2f(std::fabs(this->moveSpeed * diff), 0);
	animation.update(0, diff, faceRight);
	sprite.setTextureRect(animation.getIntRect());
	move(movement);

	if (this->getPosition().x > this->getEndPos().x)
	{
		this->setPosition(this->getBackPos());
	}
}

//---------------------------------------------------------------------------------------

Villain::Villain() :
	Enemy()
{
	// Ustawienie rz�du aniamcji, tekstury i sprite'a
	sf::Texture * texture = new sf::Texture;
	if (!(*texture).loadFromFile("Grafiki/Villain.png"))
		std::cout << "Blad wczytywania tekstury!" << std::endl;

	animation.setImageCount(sf::Vector2u(4, 4));
	animation.setSize(*texture);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 48, 39, 48));
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(500.0f, 500.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
}

//---------------------------------------------------------------------------------------

Villain::Villain(sf::Vector2u imageCount_, float switchTime_) :
	Enemy(imageCount_, switchTime_)
{
	// Ustawienie rz�du aniamcji, tekstury i sprite'a
	if (!(*texture).loadFromFile("Grafiki/zombie.png"))
		std::cout << "Blad wczytywania tekstury!" << std::endl;
	animation.setSize(*texture);
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(500.0f, 500.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
}

//---------------------------------------------------------------------------------------

Villain::Villain(sf::Texture * texture_, sf::Vector2u imageCount_, float switchTime_) :
	Enemy(texture_, imageCount_, switchTime_)
{
	// Ustawienie rz�du aniamcji, tekstury i sprite'a
	animation.setSize(*texture);
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(500.0f, 500.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
}

//---------------------------------------------------------------------------------------

Villain::~Villain()
{
	;
}

//---------------------------------------------------------------------------------------

void Villain::update(float diff)
{
	//sprite.setScale(0.5f, 0.5f);

	// Je�eli wr�g jest obr�cony w prawo
	if (faceRight)
	{
		animation.update(2, diff, faceRight);
		movement = sf::Vector2f(std::fabs(this->moveSpeed * diff), 0);

		if (this->getPosition().x > this->getEndPos().x)
		{
			this->faceRight = false;
		}
	}
	// Je�eli wr�g obr�cony jest w lewo
	else
	{
		animation.update(1, diff, faceRight);
		movement = sf::Vector2f(-std::fabs(this->moveSpeed * diff), 0);

		if (this->getPosition().x < this->getBackPos().x)
		{
			this->faceRight = true;
		}
	}

	sprite.setTextureRect(animation.getIntRect());
	move(movement);
}