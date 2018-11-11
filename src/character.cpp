#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Character::Character() :
	Moveable(), animation(), name("unknown"), health(10), mana(10)
{
	// Inicjalizacja zmiennych dotycz¹cych ruchu
	tempDelta = 0.0;
	offset = 0.0f;
	gravity = 5.0f;
	moveSpeed = 100.0f;
	jumpSpeed = 300.0f;
	groundHeight = 620.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);

	// Ustawienie flag dotycz¹cych ruchu
	faceRight = true;
	isJumping = false;
	isFalling = false;
	canMoveRight = true;
	canMoveLeft = true;
	canJump = true;
	canFall = false;
	isColliding = false;
	lastDirection = UNKNOWN;

	// Ustawienie rzêdu aniamcji, tekstury i sprite'a
	row = 1;
	if (!(*texture).loadFromFile("Grafiki/warlock_of.png"))
		std::cout << "Blad wczytywania tekstury!" << std::endl;
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(50.0f, 50.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
	pendingSpell = false;
}

//---------------------------------------------------------------------------------------

Character::Character(sf::Texture * texture_) :
	Moveable(), animation(texture_), name("unknown"), health(10), mana(10)
{
	// Inicjalizacja zmiennych dotycz¹cych ruchu
	tempDelta = 0.0;
	offset = 0.0f;
	gravity = 5.0f;
	moveSpeed = 100.0f;
	jumpSpeed = 300.0f;
	groundHeight = 620.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);

	// Ustawienie flag dotycz¹cych ruchu
	faceRight = false;
	isJumping = false;
	isFalling = false;
	canMoveRight = true;
	canMoveLeft = true;
	canJump = true;
	canFall = false;
	isColliding = false;
	lastDirection = UNKNOWN;

	// Ustawienie rzêdu aniamcji, tekstury i sprite'a
	row = 1;
	texture = texture_;
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(50.0f, 50.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
	pendingSpell = false;
}

//---------------------------------------------------------------------------------------

Character::Character(sf::Vector2u imageCount_, float switchTime_) :
	Moveable(), animation(imageCount_, switchTime_), name("unknown"), health(10), mana(10)
{
	// Inicjalizacja zmiennych dotycz¹cych ruchu
	tempDelta = 0.0;
	offset = 0.0f;
	gravity = 5.0f;
	moveSpeed = 100.0f;
	jumpSpeed = 300.0f;
	groundHeight = 620.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);

	// Ustawienie flag dotycz¹cych ruchu
	faceRight = false;
	isJumping = false;
	isFalling = false;
	canMoveRight = true;
	canMoveLeft = true;
	canJump = true;
	canFall = false;
	isColliding = false;
	lastDirection = UNKNOWN;

	// Ustawienie rzêdu aniamcji, tekstury i sprite'a
	row = 1;
	if (!(*texture).loadFromFile("Grafiki/warlock_of.png"))
		std::cout << "Blad wczytywania tekstury!" << std::endl;
	sprite.setTexture(*texture);
	sprite.setScale(1.0f, 1.0f);
	sprite.setPosition(50.0f, 50.0f);
	sprite.setOrigin(sprite.getPosition() / 2.0f);
	pendingSpell = false;
};

//---------------------------------------------------------------------------------------

Character::Character(sf::Texture * texture_, sf::Vector2u imageCount_, float switchTime_) :
	Moveable(), animation(texture_, imageCount_, switchTime_), name("unknown"), health(10), mana(10)
{
	// Inicjalizacja zmiennych dotycz¹cych ruchu
	tempDelta = 0.0;
	offset = 0.0f;
	gravity = 5.0f;
	moveSpeed = 100.0f;
	jumpSpeed = 300.0f;
	groundHeight = 620.0f;
	movement = sf::Vector2f(0.0f, 0.0f);
	coords = sf::Vector2i(0, 0);

	// Ustawienie flag dotycz¹cych ruchu
	faceRight = false;
	isJumping = false;
	isFalling = false;
	canMoveRight = true;
	canMoveLeft = true;
	canJump = true;
	canFall = false;
	isColliding = false;
	lastDirection = UNKNOWN;

	// Ustawienie rzêdu aniamcji, tekstury i sprite'a
	row = 1;
	if (!(*texture).loadFromFile("Grafiki/warlock_of.png"))
		std::cout << "Blad wczytywania tekstury!" << std::endl;
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

// Metoda ustawiaj¹ca imiê postaci
void Character::setName(const std::string & name_)
{
	this->name = name_;
}
//---------------------------------------------------------------------------------------

// Metoda ustawiaj¹ca ¿ycie postaci
void Character::setHealth(int health_)
{
	this->health = health_;
}

//---------------------------------------------------------------------------------------

// Metoda ustawiaj¹ca iloœæ many postaci
void Character::setMana(int mana_)
{
	this->mana = mana_;
}

//---------------------------------------------------------------------------------------

// True - porusza siê w prawo, false - porusza siê w lewo
void Character::setDirection(bool goRight)
{
	if (!goRight)
		this->faceRight = false;
	else
		this->faceRight = true;
}

//---------------------------------------------------------------------------------------

void Character::setCollisionState(bool collision)
{
	this->isColliding = collision;
}

//---------------------------------------------------------------------------------------

// Metoda sprawdzaj¹ca czy postaæ porusza siê w prawo
bool Character::isFacingRight()
{
	if (!(this->faceRight))
		return false;
	else
		return true;
}

//---------------------------------------------------------------------------------------

bool Character::isSpellPending()
{
	if (pendingSpell)
	{
		return true;
	}
	else
	{
		return false;
	}
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

// Metoda aktualizuj¹ca pozycjê gracza
void Character::update(float diff)
{
	movement = sf::Vector2f(0.0f, 0.0f);

	// Gdy postaæ chce siê przesun¹æ w lewo
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

	// Gdy postaæ chce siê przesun¹æ w prawo
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

	// Gdy postaæ chce skoczyæ
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

	// Je¿eli postaæ skacze
	if (isJumping == true)
	{
		offset -= gravity;
		movement.y -= offset*diff;
		// Je¿eli postaæ osi¹gnie maksymaln¹ d³ugoœæ skoku
		if (offset <= 0)
		{
			isJumping = false;
			isFalling = true;
			offset = 0.0f;
		}
		lastDirection = UP;
	}

	// Je¿eli postaæ spada
	if (isFalling == true)
	{
		offset += gravity;
		movement.y += offset*diff;
		lastDirection = DOWN;

		// Dopóki postaæ nie dotyka poziomu pod³o¿a
		if (this->getSprite().getPosition().y > groundHeight) // + this->getSprite().getGlobalBounds().height
		{
			isJumping = false;
			isFalling = false;
			offset = 0.0f;
			movement.y = 0;
			lastDirection = RIGHT;
		}
	}

	// Zdejmij debuffy z postaci
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

	// Je¿eli postaæ nie porusza siê
	if (movement.x == 0.0f && movement.y == 0.0f)
	{
		return;
	}
	// Je¿eli zosta³ dokonany jakiœ ruch
	else
	{
		animation.update(row, diff, faceRight);
		sprite.setTextureRect(animation.getIntRect());
		sprite.move(movement);
		// std::cout << "Player moved " << movement.x << "," << movement.y << std::endl;
		lastMovement = movement;
		// std::cout << "Move: " << movement.x << std::endl;
		return;
	}
}

//---------------------------------------------------------------------------------------

// Metoda rysuj¹ca postaæ
void Character::draw(sf::RenderWindow & window_)
{
	window_.draw(sprite);
}

//---------------------------------------------------------------------------------------

bool Character::collision(Entity * entity)
{
	// Je¿eli nadesz³a kolizja z kafelkiem
	if (typeid(*entity) == typeid(Tile))
	{
		// Pobierane jest ID kafelka w celu jego jednoznacznego zidentyfikowania
		switch (entity->getID())
		{

		// Je¿eli tym kafelkiem by³ STONE_1
		case 1:
		{
			std::cout << "Collision with: Stone detected!" << std::endl;
		}

		// Je¿eli tym kafelkiem by³ BRICK_1
		case 3:
		{
			std::cout << "Collision with: Brick deteced!" << std::endl;
			isColliding = true;

			// Kolizja z prawej strony
			if (this->getLastMovement().x > 0)
			{
				this->move(sf::Vector2f(-abs(this->getLastMovement().x), 0));

				if (this->getSprite().getPosition().y + this->getSprite().getGlobalBounds().height < groundHeight && isJumping == false)
				{
					this->isFalling = true;
				}
			}

			// Kolizja z lewej strony
			else if (this->getLastMovement().x < 0)
			{
				this->move(sf::Vector2f(abs(this->getLastMovement().x), 0));

				if (this->getSprite().getPosition().y + this->getSprite().getGlobalBounds().height < groundHeight && isJumping == false)
				{
					this->isFalling = true;
				}
			}

			// Kolizja z do³u
			if (this->getLastMovement().y < 0)
			{
				this->isJumping = false;
				this->isFalling = true;
				this->move(sf::Vector2f(0, abs(this->getLastMovement().y)));
			}

			// Kolizja z góry
			else if (this->getLastMovement().y > 0)
			{
				this->isJumping = false;
				this->isFalling = false;
				this->move(sf::Vector2f(0, -abs(this->getLastMovement().y)));
				this->movement.y = 0;
			}

			break;
		}

		// Je¿eli tym kafalkiem by³ LAVA_1
		case 5:
		{
			// std::cout << "Collision with: Lava detected!" << std::endl;
			this->hurt(3);
		}

		// Je¿eli tym kafelkiem by³ WATER_1
		case 7:
		{
			// std::cout << "Collision with: Water detected!" << std::endl;
			this->slow(1);
		}
		default:
			break;
		}

	}

	// Je¿eli nadesz³a kolizja z monet¹
	else if (typeid(*entity) == typeid(Coin)) // else if (typeid(entity) == typeid(Coin))
	{
		//std::cout << "Collision with: Coin detected!" << std::endl;
	}

	// Je¿eli nadesz³a kolizja z przeciwnikiem
	else if (typeid(*entity) == typeid(Enemy)) // else if (typeid(entity) == typeid(Coin))
	{
		//std::cout << "Collision with: Enemy detected!" << std::endl;
		this->hurt(3);
	}

	//Je¿eli na liœcie nie zosta³ uwzglêdniony obiekt
	else
		//std::cout << "Unknown object!" << std::endl;

	//isColliding = false;

	return true;
}

//---------------------------------------------------------------------------------------