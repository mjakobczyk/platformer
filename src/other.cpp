#include "../include/basic.h"

// Funkcja sprawdzaj¹ca dzia³anie biblioteki SFML
void test()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) // G³ówna pêtla programu
	{
		sf::Event event;
		// Event jest kontenerem zdarzeñ, w którym przechowuje siê informacje o wciœniêciu
		// okreœlonych klawiszy. Dziêki temu mo¿na w odpowiedzi sposób reagowaæ.

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}

// Funkcja sprawdzaj¹ca dzia³anie biblioteki SFML 2
void test2()
{
	sf::RenderWindow window1;
	window1.create(sf::VideoMode(WIDTH, HEIGHT), "Gra_1", sf::Style::Close);
	window1.setVerticalSyncEnabled(true);
	window1.setFramerateLimit(FPS);

	Menu * menu = new MainMenu;

	while (window1.isOpen()) // G³ówna pêtla programu
	{
		sf::Event event;
		// Event jest kontenerem zdarzeñ, w którym przechowuje siê informacje o wciœniêciu
		// okreœlonych klawiszy. Dziêki temu mo¿na w odpowiedzi sposób reagowaæ.

		while (window1.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window1.close();
		}

		window1.clear();
		menu->draw(window1);
		window1.display();
	}
}

// Funkcja sprawdzaj¹ca dzia³anie biblioteki SFML 3
void test3()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(WIDTH, HEIGHT), "MOJA_GRA", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(FPS);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("Grafiki/warlock_of.png");

	Hero * player = new Warlock;
	sf::Sprite temp;
	temp.setTexture(*(player->getTexture()));
	temp.setPosition(400.0f, 400.0f);

	float delta = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		delta = clock.restart().asSeconds();
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			default:
				break;
			}
		}

		player->Character::update(delta);
		window.clear(sf::Color(150, 150, 150));
		//window.draw(backgroundS); // background
		player->Character::draw(window);
		window.draw(temp);
		window.display();
	}

	return;
}

void test4()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(WIDTH, HEIGHT), "MOJA_GRA", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(FPS);

	Hero * player = new Warlock;
	player->setPosition(sf::Vector2f(700, 700));
	Zombie * zombie = new Zombie;
	zombie->setPosition(sf::Vector2f(400, 300));
	zombie->setStartPos(sf::Vector2f(400, 300));
	zombie->setEndPos(sf::Vector2f(700, 300));
	zombie->setBackPos(sf::Vector2f(400, 300));
	Fireball * fireball = new Fireball;
	fireball->setStartingPos(sf::Vector2f(300, 300));

	float delta = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		delta = clock.restart().asSeconds();
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			default:
				break;
			}
		}

		window.clear(sf::Color(150, 150, 150));
		player->update(delta);
		zombie->Zombie::update(delta);
		fireball->update(delta);

		player->draw(window);
		zombie->draw(window);
		fireball->draw(window);
		window.display();
	}

	return;
}

// Funkcja pomocnicza zwracaj¹ca aktualn¹ datê i godzinê
std::string pobierzAktualnyCzas()
{
	time_t czas; // Deklaracja zmiennej przechowuj¹cej czas
	time(&czas); // Pobranie aktualnego czasu z systemu
	return ctime(&czas); // Wartoœci¹ zwracan¹ jest string z ca³¹ dat¹ i godzina
}

// Funkcja konwertuj¹ca sekundy na postaæ minuty-sekundy
std::string convertSecondsToMinutes(float time)
{
	int total, seconds, minutes;
	std::ostringstream ss;
	total = static_cast<int>(std::round(time));
	minutes = total / 60;
	seconds = total % 60;
	ss << minutes << ":" << seconds;
	return ss.str();
}

// Funkcja konwertuj¹ca liczbê ca³kowit¹ na ³añcuch tekstowy
std::string convertIntToString(int number)
{
	std::ostringstream ss;
	ss << number;
	return ss.str();
}