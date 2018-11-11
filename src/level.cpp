#include "../include/basic.h"

//---------------------------------------------------------------------------------------

int Level::points = 0;
float Level::time = 0;

//---------------------------------------------------------------------------------------

Level::Level(sf::RenderWindow & window_, Hero *& hero_) : 
	window(window_), hero(hero_), interface(hero_)
{
	// Inicjalizacja kamery
	camera.setSize(WIDTH, HEIGHT);
	camera.setCenter(WIDTH / 2, HEIGHT / 2);

	// Inicjalizujemy zmienne specjalne
	isActive = true;
	isCompleted = false;

	// Inicjalizacja koordynatów na mapie dla gracza
	startX = 0.0f;
	startY = 0.0f;

	// Inicjalizacja zmiennych czasowych
	switchTime = 10.0f; // Przyk³adowy switchtime, mo¿na daæ wolniejszy
	totalTime = 0.0f; // Ca³kowity czas inicjalizujemy 0
	delta = 0.02f; // Odstêp miêdzy kolejnymi przejœciami

	// Inicjalizacja t³a
	backgroundT.loadFromFile("Grafiki/backg4.jpg");
	backgroundS.setTexture(backgroundT);

	// Inicjalizacja nazwy poziomu i jego numeru
	levelName = "Level 0.";
	levelNumber = 0;
	
	// Inicjalizacja licznika
	clock.restart().asSeconds();

	// Za³adowanie tekstur do wektora
	sf::Texture * temp = new sf::Texture;
	if (!(temp->loadFromFile("Grafiki/brick_1.png")))
		std::cout << "Blad z odczytem pliku do tekstury!" << std::endl;
	else
		std::cout << "Wczytano poprawnie teksture!!" << std::endl;
	textures.push_back(temp);
}

//---------------------------------------------------------------------------------------

Level::~Level()
{
	// Usuniêcie wszystkich tekstur
	for (std::vector<sf::Texture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if (*it != nullptr) delete *it;
	}
	
	textures.clear();

	// Usuniêcie wszystkich obiektów sta³ych
	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if (*it != nullptr) delete *it;
	}

	stableObjects.clear();

	// Usuniêcie wszystkich obiektów poruszaj¹cych siê
	for (std::vector<Moveable*>::iterator it = moveableObjects.begin(); it != moveableObjects.end(); ++it)
	{
		if (*it != nullptr) delete *it;
	}

	moveableObjects.clear();

	// Usuniêcie wszystkich obiektów poruszaj¹cych siê
	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (*it != nullptr) delete *it;
	}

	enemies.clear();

	// Usuniêcie wszystkich czarów
	for (std::vector<Spell*>::iterator it = spells.begin(); it != spells.end(); ++it)
	{
		if (*it != nullptr) delete *it;
	}

	spells.clear();
}

//---------------------------------------------------------------------------------------

void Level::setLevel(sf::RenderWindow & window, const std::string & fileName)
{
	if (!this->loadFromFile(fileName))
	{
		std::cout << "Nie udalo sie zaladowac levela do pamieci!" << std::endl;
		return;
	}

	this->updateLevel(delta);
	window.setView(camera);
}

//---------------------------------------------------------------------------------------

bool Level::loadFromFile(const std::string & fileName)
{
	std::cout << "Wczytuje poziom z pliku..." << std::endl;
	// Zmienna do obs³ugi strumienia wejœciowego
	std::fstream file;
	file.open(fileName, std::ios::in);
	if (!file.good())
	{
		std::cout << "Blad z odczytem poziomu z pliku!" << std::endl;
		return false;
	}

	// Zczytane g³ównych wspó³rzêdnych mapy i obs³uga b³êdu
	file >> width >> height; 

	if (width <= 0 || height <= 0)
	{
		std::cout << "Niepoprawny rozmiar mapy z pliku!" << std::endl;
		file.close();
		return false;
	}

	std::cout << "Zczytane wartosci: width = " << width << " ; height = " << height << std::endl;

	// Inicjalizacja rozmiaru widzialnej czêœci mapy
	std::cout << "Inicjalizuje klase poziom!" << std::endl;
	//visibleWidth = (window.getSize().x / TILE_WIDTH) + 2;
	//visibleHeight = (window.getSize().y / TILE_HEIGHT) + 2;
	visibleWidth = (WIDTH / TILE_WIDTH); // TUTAJ BYLO + 2 !!!!!!!!!
	visibleHeight = (HEIGHT / TILE_HEIGHT);
	std::cout << "VisibleWidth = " << visibleWidth << std::endl;
	std::cout << "VisibleHeight = " << visibleHeight << std::endl;

	// Zmiana wielkoœci wektora widzialnych tekstur
	sprites.resize(visibleHeight);

	for (int i = 0; i < visibleHeight; ++i)
	{
		sprites[i].resize(visibleWidth);
	}

	std::cout << "Rozmiary zaalokowanego wektora sprite'ow to: [  y = " << sprites.size() << " x = " << sprites[0].size() << " ]" << std::endl;

	// Zmiana wielkoœci wektora kafelków
	tiles.resize(height);

	for (int i = 0; i < height; i++)
	{
		tiles[i].resize(width);
	}

	std::cout << "Rozmiary zaalokowanego wektora tiles'ow to: [  y = " << tiles.size() << " x = " << tiles[0].size() << " ]" << std::endl;

	// Je¿eli wszystko jest poprawne to zczytujemy koordynaty
	std::cout << "Zczytuje koordynaty kafelkow." << std::endl;

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			Tile tile;
			short numberRead;
			file >> numberRead;
			if (numberRead != 0)
			{
				Tile * obstacleTile = new Tile;
				obstacleTile = obstacleTile->getTilePointer(numberRead);
				obstacleTile->setPosition(sf::Vector2f(static_cast<float>(j*TILE_HEIGHT), static_cast<float>(i*TILE_WIDTH)));
				obstacles.push_back(obstacleTile);
			}
			tiles[i][j] = tile.getTile(numberRead);
		}
	}

	file.clear();

	std::cout << "Poprawnie zczytano koordynaty kafelkow!" << std::endl;

	// Zczytywanie obiektów specjalnych
	std::cout << "Zczytuje obiekty specjalne." << std::endl;

	while (!file.eof())
	{
		std::string line, objName;
		sf::Vector2i coords;
		sf::Vector2f position;
		Tile tempTile;

		std::getline(file, line, '\n');
		std::istringstream iss(line); // Zmienna do parsowania stringa

		if (!iss.good()) std::cout << "Blad z lancuchem tekstowym!";  // Obs³uga b³êdów
		iss >> objName >> coords.x >> coords.y;
		position = sf::Vector2f(static_cast<float>(coords.x * TILE_WIDTH), static_cast<float>(coords.y * TILE_HEIGHT));

		// Je¿eli zczytanym obiektem jest Coin
		if (objName == "Coin")
		{
			Coin * newCoin = new Coin;
			newCoin->setCoords(coords);
			newCoin->setPosition(position);
			stableObjects.push_back(newCoin);
			std::cout << "Coin koordynaty: " << position.x << " " << position.y << std::endl;
		}

		// Je¿eli zczytanym obiektem jest portal wyjœciowy
		else if (objName == "Out")
		{
			Tile * newTile = new Tile;
			newTile = tempTile.getTilePointer(9);
			newTile->setCoords(coords);
			newTile->setPosition(position);
			stableObjects.push_back(newTile);
			std::cout << "Door koordynaty: " << position.x << " " << position.y << std::endl;
		}

		// Je¿eli zczytanym obiektem jest Zombie
		else if (objName == "Zombie")
		{
			Zombie * zombie = new Zombie;
			zombie->setStartPos(position);
			zombie->setPosition(position);
			enemies.push_back(zombie);
			std::cout << "Zombie koordynaty: " << position.x << " " << position.y << std::endl;
		}

		// Je¿eli zczytanym obiektem jest Villain
		else if (objName == "Villain")
		{
			Villain * villain = new Villain;
			villain->setStartPos(position);
			villain->setPosition(position);
			enemies.push_back(villain);
			std::cout << "Villain koordynaty: " << position.x << " " << position.y << std::endl;
		}
	}

	std::cout << "Poprawnie zczytano obiekty specjalne!" << std::endl;

	file.close();
	std::cout << "Wczytywanie poziomu z pliku zakonczone sukcesem!" << std::endl;
	return true;
}

//---------------------------------------------------------------------------------------

void Level::setLevelSize(unsigned int width_, unsigned int height_)
{
	this->width = width_;
	this->height = height_;
}

//---------------------------------------------------------------------------------------

void Level::setLevelNumber(unsigned short levelNumber_)
{
	this->levelNumber = levelNumber_;
}

//---------------------------------------------------------------------------------------

void Level::setLevelName(const std::string & levelName_)
{
	this->levelName = levelName_;
}

//---------------------------------------------------------------------------------------

void Level::setLevelBackGround(sf::Texture * backgroundT_)
{
	this->backgroundT = (*backgroundT_);
	this->backgroundS.setTexture(this->backgroundT);
}

//---------------------------------------------------------------------------------------

void Level::resetPoints()
{
	this->points = 0;
}

//---------------------------------------------------------------------------------------

void Level::resetTime()
{
	this->time = 0;
}

//---------------------------------------------------------------------------------------

sf::Time Level::getCurrentTime()
{
	return (this->clock.getElapsedTime());
}

//---------------------------------------------------------------------------------------

int Level::getPoints()
{
	return this->points;
}

//---------------------------------------------------------------------------------------

float Level::getTime()
{
	return this->time;
}

//---------------------------------------------------------------------------------------

void Level::awardPoint(int score)
{
	this->points += score;
}

//---------------------------------------------------------------------------------------

void Level::updateLevel(float delta)
{
	// Tymczasowy wektor wskazuj¹cy gdzie powinna znajdowaæ siê kamera
	sf::Vector2i fixed(hero->getCoords());
	camera.setCenter(fixed.x*TILE_WIDTH + TILE_WIDTH / 2, HEIGHT / 2);

	// Wspó³rzêdne kamery:
	// std::cout << "X = " << camera.getCenter().x << " ; Y = " << camera.getCenter().y;

	// Obliczenie pozycji minimalnych granic kamery
	sf::Vector2f min = sf::Vector2f(camera.getCenter().x - camera.getSize().x / 2, camera.getCenter().y - camera.getSize().y / 2);

	// Ustawienie kamery w poziomie
	int leftBorder = min.x / TILE_WIDTH;
	int rightBorder = leftBorder + this->visibleWidth - 2;

	// Je¿eli jest za daleko na lewo
	if (min.x < 0)
	{
		// Ró¿nica pomiêdzy 0, a lew¹ krawêdzi¹
		int difference = abs(min.x);
		min.x += difference;
		camera.move(difference, 0);

		leftBorder = min.x / TILE_WIDTH;
	}
	else if (leftBorder > 0 && rightBorder - 1 < this->width - 1)
	{
		min.x -= TILE_WIDTH;
		camera.move(-TILE_WIDTH, 0);

		leftBorder = min.x / TILE_WIDTH;
	}

	else if (rightBorder - 1 >= this->width - 1)
	{
		int difference = camera.getCenter().x + camera.getSize().x / 2 - (this->width - 1)*TILE_WIDTH;

		difference = -difference - TILE_WIDTH;
		min.x += difference;

		leftBorder = (min.x) / TILE_WIDTH;

		camera.setCenter((leftBorder + (this->visibleWidth) / 2)*TILE_WIDTH + TILE_WIDTH, camera.getCenter().y);
	}
	else if (leftBorder == 0)
		camera.move(-TILE_WIDTH , 0);

	// Ustawienie kamery w kierunku pionowym
	int upBorder = min.y / TILE_HEIGHT;
	int bottomBorder = upBorder + this->visibleHeight + 1;

	// Je¿eli kamera jest za bardzo wysuniêta do góry
	if (min.y < 0)
	{
		int difference = abs(min.y);
		min.y += difference;
		camera.move(0, difference);

		upBorder = min.y / TILE_WIDTH;

	}
	else if (upBorder > 0 && bottomBorder - 1 < this->height - 1)
	{
		min.y -= TILE_HEIGHT;
		camera.move(0, -TILE_HEIGHT);

		upBorder = min.y / TILE_HEIGHT;
	}
	else if (bottomBorder - 1 >= this->height - 1)
	{
		int difference = camera.getCenter().y + camera.getSize().y / 2 - (this->height - 1)*TILE_HEIGHT;

		difference = -difference - TILE_HEIGHT;
		min.y += difference;

		upBorder = (min.y) / TILE_HEIGHT;

		camera.setCenter(camera.getCenter().x, (upBorder + (this->visibleHeight) / 2)*TILE_HEIGHT + TILE_HEIGHT);

		if (bottomBorder - 1 == this->visibleHeight - 1)           // !!!
			camera.move(0, -TILE_HEIGHT / 2);
	}
	else if (upBorder == 0)
		camera.move(0, -TILE_HEIGHT / 2);

	if (leftBorder < 0) leftBorder = abs(leftBorder);
	if (upBorder < 0) upBorder = abs(upBorder);	

	// Ustawienie kafli na scenie
	for (int y = 0, h = 0; y < this->visibleHeight; y++)		  // h - horizontal
	{          
		for (int x = 0, v = 0; x < this->visibleWidth; x++)       // v - vertical
		{
			//sprites[y][x].setPosition(v*TILE_HEIGHT, h*TILE_WIDTH);
			//sprites[y][x].setTexture((*tiles[h][v].getTexture()));
			tiles[y][x].setPosition((sf::Vector2f(v*TILE_HEIGHT, h*TILE_WIDTH)));
			v++;
		}
		h++;
	}

	// std::cout << "Poziom zostal zaktualizowany pomyslnie!" << std::endl;
}

//---------------------------------------------------------------------------------------

sf::Vector2i Level::checkCollisions(Entity * entity, Direction direction)
{
	int x = (int)(entity->getSprite().getPosition().x + entity->getSprite().getGlobalBounds().width / 2) / TILE_WIDTH;
	int y = (int)(entity->getSprite().getPosition().y + entity->getSprite().getGlobalBounds().height / 2) / TILE_HEIGHT;

	switch (direction)
	{
	case LEFT:
		x = (int)(entity->getSprite().getPosition().x + entity->getSprite().getGlobalBounds().width) / TILE_WIDTH;
		y = (int)(entity->getSprite().getPosition().y + entity->getSprite().getGlobalBounds().height / 2) / TILE_HEIGHT;
		break;
	case RIGHT:
		x = (int)(entity->getSprite().getPosition().x) / TILE_WIDTH;
		y = (int)(entity->getSprite().getPosition().y + entity->getSprite().getGlobalBounds().height / 2) / TILE_HEIGHT;
		break;
	case UP:
		x = (int)(entity->getSprite().getPosition().x + entity->getSprite().getGlobalBounds().width / 2) / TILE_WIDTH;
		y = (int)(entity->getSprite().getPosition().y) / TILE_HEIGHT;
		break;
	case DOWN:
		x = (int)(entity->getSprite().getPosition().x + entity->getSprite().getGlobalBounds().width / 2) / TILE_WIDTH;
		y = (int)(entity->getSprite().getPosition().y + entity->getSprite().getGlobalBounds().height) / TILE_HEIGHT;
		break;
	}
	
	// Zwracamy tile, który znajduje siê na tej pozycji
	return sf::Vector2i(x, y);
}

//---------------------------------------------------------------------------------------

void Level::checkCollisions()
{
	// Badanie kolizji z obiektami sta³ymi
	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (hero->checkCollision(*it))
		{
			hero->collision(*it);

			if ((*it)->getInteraction() == BONUS)
			{
				this->awardPoint(BONUS_POINTS);
				(*it)->destroy();
			}
			else if ((*it)->getInteraction() == TELEPORT)
			{
				this->isActive = false;
				this->isCompleted = true;
			}
		}
	}

	// Badanie kolizji z obiektami ruchomymi
	for (std::vector<Moveable*>::iterator it = moveableObjects.begin(); it != moveableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (hero->checkCollision(*it))
		{
			hero->collision(*it);
		}
	}

	// Badanie kolizji z przeciwnikami
	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (*it == nullptr) continue;

		if (hero->checkCollision(*it))
		{
			hero->collision(*it);
			hero->hurt(1);
		}

		// Badanie kolizji czarów z przeciwnikami
		for (std::vector<Spell*>::iterator itt = spells.begin(); itt != spells.end(); ++itt)
		{
			if (*itt == nullptr) continue;

			if ((*itt)->checkCollision(*it))
			{
				this->awardPoint(ZOMBIE_BONUS);
				(*itt)->destroy();

				if (*it == nullptr) continue;

				(*it)->destroy();
			}
		}
	}

	// Badanie kolizji z przeszkodami
	for (std::vector<Tile*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		if (hero->checkCollision(*it))
		{
			hero->collision(*it);
		}

		for (std::vector<Spell*>::iterator itt = spells.begin(); itt != spells.end(); ++itt)
		{
			if (*itt == nullptr) continue;

			if ((*itt)->checkCollision(*it))
			{
				(*itt)->destroy();
			}
		}
	}
}

//---------------------------------------------------------------------------------------

void Level::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->hero->castSpell())
		{
			Spell * temp = hero->getSpell();
			temp->setStartingPos(hero->getPosition());
			temp->setPosition(sf::Vector2f(hero->getPosition().x, hero->getPosition().y));
			temp->setDirection(hero->isFacingRight());
			spells.push_back(temp);
		}
	}

	// Z góry zak³adamy, ¿e gracz z niczym nie koliduje, jeœli jest inaczej to kolejna pêtla zmieni ten stan
	hero->setCollisionState(false);

	// Aktualizacja obiektów sta³ych
	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end();)
	{
		if ((*it)->isDead())
		{
			delete (*it);
			(*it) = nullptr;
		}

		if (*it == nullptr)
		{
			it = stableObjects.erase(it);
			continue;
		}

		(*it)->update(delta);
		++it;
	}

	// Aktualizacja obiektów ruchomych
	for (std::vector<Moveable*>::iterator it = moveableObjects.begin(); it != moveableObjects.end();)
	{
		if ((*it)->isDead())
		{
			delete (*it);
			(*it) = nullptr;
		}

		if (*it == nullptr)
		{
			it = moveableObjects.erase(it);
			continue;
		}

		(*it)->update(delta);
		++it;
	}

	// Aktualizacja przeciwników
	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end();)
	{
		if ((*it)->isDead())
		{
			delete (*it);
			(*it) = nullptr;
		}

		if (*it == nullptr)
		{
			it = enemies.erase(it);
			continue;
		}

		(*it)->update(delta);
		++it;
	}

	// Aktualizacja czarów
	for (std::vector<Spell*>::iterator it = spells.begin(); it != spells.end(); )
	{
		if ((*it)->isDead())
		{
			delete (*it);
			(*it) = nullptr;
		}

		if (*it == nullptr)
		{
			it = spells.erase(it);
			continue;
		}

  		(*it)->update(delta);
		++it;
	}

	// Aktualizacja gracza
	hero->update(delta);

	// Sprawdzenie warunku zakoñczenia poziomu
	if (hero->getHealth() < MIN_HEALTH)
	{
		this->isActive = false;
		this->isCompleted = false;
	}

	// Rysowanie interfejsu
	interface.update(this->getCurrentTime(), this->getPoints());
}

//---------------------------------------------------------------------------------------

void Level::draw()
{
	// Czyszczenie okna, aktualizacja kafli i gracza
	window.clear(sf::Color(150, 170, 190));

	// Rysowanie t³a
	window.draw(backgroundS);

	// Rysowanie obiektów sta³ych
	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		(*it)->draw(window);
	}

	// Rysowanie obiektów ruchomych
	for (std::vector<Moveable*>::iterator it = moveableObjects.begin(); it != moveableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		(*it)->draw(window);
	}

	// Rysowanie przeciwników
	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (*it == nullptr) continue;

		(*it)->draw(window);
	}

	// Rysowanie przeszkód
	for (std::vector<Tile*>::iterator it = obstacles.begin(); it != obstacles.end(); ++it)
	{
		if (*it == nullptr) continue;

		window.draw((*it)->getSprite());
	}

	// Rysowanie czarów
	for (std::vector<Spell*>::iterator it = spells.begin(); it != spells.end(); ++it)
	{
		if (*it == nullptr) continue;

		(*it)->draw(window);
	}

	// Rysowanie gracza i interfejsu
	interface.draw(window);
	hero->draw(window);

	// Ustawienie kamery na œrodku ekranu
	window.setView(camera);
	window.display();
}

//---------------------------------------------------------------------------------------

bool Level::play(sf::RenderWindow & window, Hero *& hero)
{
	// Ustawienie pozycji gracza
	this->hero->setPosition(sf::Vector2f(startX, startY));

	// Ustawienie efektów czasowych
	this->clock.restart().asSeconds();

	// Dopóki okno gry jest owarte
	while (window.isOpen() && this->isActive)
	{
		// Sprawdzenie wszystkich kolizji
		this->checkCollisions();

		// Aktualizacja wszystkich obiektów
		this->update();

		// Rysowanie wszystkich obiektów
		this->draw();
	}

	// Przed wyjœciem aktualizujemy informacje o statystykach
	this->time += clock.getElapsedTime().asSeconds();

	// Zwracamy czy poziom uda³o siê przejœæ, czy zakoñczono grê
	return this->isCompleted;
}

//---------------------------------------------------------------------------------------

Level_01::Level_01(sf::RenderWindow & window, Hero *& hero) :
	Level(window, hero)
{
	// Inicjalizacja koordynatów na mapie dla gracza
	startX = 32.0f;
	startY = 620.0f;

	// Inicjalizacja t³a
	backgroundT.loadFromFile("Grafiki/backg5.png");
	backgroundS.setTexture(backgroundT);

	// Inicjalizacja nazwy poziomu i jego numeru
	this->setLevelName("Level_1");
	this->setLevelNumber(1);

	// Ustawienie odpowiedniej poziomu z pliku
	setLevel(this->window, "Levele/level_01.txt");

	// Ustawienie informacji o poruszaj¹cych siê obiektach
	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (typeid(**it) == typeid(Zombie))
		{
			(*it)->setBackPos(sf::Vector2f(34 * TILE_WIDTH, (*it)->getStartPos().y));
			(*it)->setEndPos(sf::Vector2f(45 * TILE_WIDTH, (*it)->getStartPos().y));
			(*it)->setMoveSpeed(150.0f);
		}
		else if (typeid(**it) == typeid(Villain))
		{
			(*it)->setBackPos(sf::Vector2f((22) * TILE_WIDTH, (*it)->getStartPos().y));
			(*it)->setEndPos(sf::Vector2f((28) * TILE_WIDTH, (*it)->getStartPos().y));
		}
	}

	// Ustawienie pozycji gracza
	this->hero->getSprite().setScale(sf::Vector2f(1.0f, 1.0f));
	this->hero->setPosition(sf::Vector2f(startX, startY));
}

//---------------------------------------------------------------------------------------

Level_01::~Level_01()
{
	;
}

//---------------------------------------------------------------------------------------

Level_02::Level_02(sf::RenderWindow & window, Hero *& hero) :
	Level(window, hero)
{
	// Inicjalizacja koordynatów na mapie dla gracza
	startX = 32.0f;
	startY = 620.0f;

	// Inicjalizacja t³a
	backgroundT.loadFromFile("Grafiki/backg5.png");
	backgroundS.setTexture(backgroundT);

	// Inicjalizacja nazwy poziomu i jego numeru
	this->setLevelName("Level_2");
	this->setLevelNumber(2);

	// Ustawienie odpowiedniej poziomu z pliku
	setLevel(this->window, "Levele/level_02.txt");

	// Ustawienie informacji o poruszaj¹cych siê obiektach
	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it)
	{
		if (typeid(**it) == typeid(Zombie))
		{
			(*it)->setBackPos(sf::Vector2f(5 * TILE_WIDTH, (*it)->getStartPos().y));
			(*it)->setEndPos(sf::Vector2f(37 * TILE_WIDTH, (*it)->getStartPos().y));
			(*it)->setMoveSpeed(300.0f);
		}
		else if (typeid(**it) == typeid(Villain))
		{
			(*it)->setBackPos(sf::Vector2f((13) * TILE_WIDTH, (*it)->getStartPos().y));
			(*it)->setEndPos(sf::Vector2f((39) * TILE_WIDTH, (*it)->getStartPos().y));
			(*it)->setMoveSpeed(200.0f);
		}
	}

	// Ustawienie pozycji gracza
	this->hero->getSprite().setScale(sf::Vector2f(1.0f, 1.0f));
	this->hero->setPosition(sf::Vector2f(startX, startY));
}

//---------------------------------------------------------------------------------------

Level_02::~Level_02()
{
	;
}

//---------------------------------------------------------------------------------------