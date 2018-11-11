#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Interface::Interface(Hero * & hero_) :
	hero (hero_)
{
	if (!font.loadFromFile("Czcionki/blockss.otf")) // "Czcionki/blockss.otf"
	{
		std::cout << "Blad odczytu czcionki!" << std::endl;
		return;
	}

	for (int i = 0; i < INTERFACE_BUTTONS_QUANTITY; ++i)
	{
		Button * tmp = new Button;
		tmp->setFont(Interface::font);
		tmp->setColor(sf::Color::Green);
		tmp->setSize(60);
		switch (i)
		{
		case 0: 
		{
			tmp->setName("HP: "); 
			tmp->setPos(sf::Vector2f(60, 670));
			break;
		}
		case 1:
		{
			tmp->setName("x ");
			tmp->setPos(sf::Vector2f(230, 670));
			break;
		}
		case 2:
		{
			tmp->setName("3");
			tmp->setPos(sf::Vector2f(270, 670));
			break;
		}
		case 3:
		{
			tmp->setName("Score:"); 
			tmp->setPos(sf::Vector2f(360, 670));
			break;
		}
		case 4:
		{
			tmp->setName("x ");
			tmp->setPos(sf::Vector2f(610, 670));
			break;
		}
		case 5:
		{
			tmp->setName("0");
			tmp->setPos(sf::Vector2f(640, 670));
			break;
		}
		case 6:
		{
			tmp->setName("Time:"); 
			tmp->setPos(sf::Vector2f(740, 670));
			break;
		}
		case 7:
		{
			tmp->setSize(50);
			tmp->setName("XX:XX:XX");
			tmp->setPos(sf::Vector2f(970, 680));
		}
		default: break;
		}
		buttons.push_back(tmp);
	}

	for (int i = 0; i < INTERFACE_GRAPHICS_QUANTITY; ++i)
	{
		sf::Texture * texture = new sf::Texture;
		sf::Sprite sprite;

		switch (i)
		{
		case 0:
		{
			texture->loadFromFile("Grafiki/heart.png");
			sprite.setTexture(*texture);
			sprite.setScale(sf::Vector2f(0.13f, 0.13f));
			sprite.setPosition(sf::Vector2f(170, 680));
			break;
		}
		case 1:
		{
			texture->loadFromFile("Grafiki/coin_2.png");
			sprite.setTexture(*texture);
			sprite.setScale(sf::Vector2f(0.22f, 0.22f));
			sprite.setPosition(sf::Vector2f(540, 680));
			break;
		}
		case 2:
		{
			texture->loadFromFile("Grafiki/clock.png");
			sprite.setTexture(*texture);
			sprite.setScale(sf::Vector2f(0.05f, 0.05f));
			sprite.setPosition(sf::Vector2f(900, 680));
			break;
			break;
		}
		default:
			break;
		}

		textures.push_back(texture);
		sprites.push_back(sprite);
	}
}

//---------------------------------------------------------------------------------------

Interface::~Interface()
{
	for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		if (*it != nullptr) delete *it;
	}

	for (std::vector<sf::Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if (*it != nullptr) delete *it;
	}
}

//---------------------------------------------------------------------------------------

void Interface::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < INTERFACE_BUTTONS_QUANTITY; ++i)
	{
		buttons[i]->draw(window);
	}

	for (std::vector<sf::Sprite>::iterator it = sprites.begin(); it != sprites.end(); ++it)
	{
		window.draw(*it);
	}
}

//---------------------------------------------------------------------------------------

void Interface::update(sf::Time time, float points)
{
	// Aktualizacja danych o ¿yciu gracza
	std::ostringstream ss;
	ss << hero->getHealth();
	buttons[2]->setName(ss.str());

	// Aktualizacja danych o iloœci punktów poziomu
	std::ostringstream hh;
	hh << points;
	buttons[5]->setName(hh.str());

	// Aktualizacja danych o czasie gry
	std::ostringstream tt;
	tt << time.asSeconds();
	buttons[7]->setName(tt.str());
}

//---------------------------------------------------------------------------------------