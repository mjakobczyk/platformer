#include "../include/basic.h"

//---------------------------------------------------------------------------------------

GameOver::GameOver()
{
	ID = 666;
	collidable = false;
	interactable = false;
	interaction = Interaction::NONE;
	sf::Texture * temp = new sf::Texture;
	if (!temp->loadFromFile("Grafiki/Gameover.png"))
		std::cout << "Failed to load Gameover texture!" << std::endl;

	setTexture(temp);
	coords = sf::Vector2i(0, 0);
	row = 0;
	animation.setImageCount(sf::Vector2u(1, 4));
	animation.setSize(*temp);
	animation.setSwitchTime(0.5f);
	sprite.setTextureRect(sf::IntRect(0, 0, 140, 35));
	sprite.setScale(4.0f, 4.0f);
	down = true;
	clock.restart().asSeconds();
}

//---------------------------------------------------------------------------------------

GameOver::~GameOver()
{
	;
}

//---------------------------------------------------------------------------------------

void GameOver::update(float diff)
{
	if (clock.getElapsedTime().asSeconds() > 0.1f)
	{
		// Je¿eli idziemy w dó³ z animacj¹
		if (down)
		{
			animation.update(row++, diff, true);

			if (row > 2)
				down = false;
		}
		// Je¿eli idziemy w górê z animacj¹
		else
		{
			animation.update(row--, diff, true);
			if (row < 1)
				down = true;
		}

		sprite.setTextureRect(animation.getIntRect());
		clock.restart().asSeconds();
	}
}

//---------------------------------------------------------------------------------------