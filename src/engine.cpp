#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Engine::Engine(sf::RenderWindow & window_, heroSpec heroSpec_) : window(window_)
{
	// W zale¿noœci od wybranej klasy bohater tworzy swoj¹ postaæ
	if (heroSpec_ == heroSpec::warlock)
		this->hero = new Warlock();
	else if (heroSpec_ == heroSpec::mage)
		this->hero = new Mage();
	else if (heroSpec_ == heroSpec::priest)
		this->hero = new Priest();
	else
		return;

	totalLevels = 2; // Ca³kowita liczba zaimplementowanych poziomów
	currentLevel = 1; // Zaczynamy zawsze od 1. poziomu
	bool running = false; // Identyfikacja czy gra trwa czy te¿ nie

	Level * level1 = new Level_01(window, hero);
	levels.push_back(level1);
	Level * level2 = new Level_02(window, hero);
	levels.push_back(level2);
	
	// Resetujemy punkty i czas rozgrywki przy starcie silnika
	level1->resetPoints();
	level1->resetTime();
}

//---------------------------------------------------------------------------------------

Engine::~Engine()
{
	if (!hero) delete hero;

	for (std::vector<Level*>::iterator it = levels.begin(); it != levels.end();)
	{
		if ((*it) != nullptr)
		{
			delete (*it);
			(*it) = nullptr;
		}

		if (*it == nullptr)
		{
			it = levels.erase(it);
			continue;
		}

		++it;
	}
}

//---------------------------------------------------------------------------------------

int Engine::getPoints()
{
	return this->totalStats.pts;
}

//---------------------------------------------------------------------------------------

float Engine::getTime()
{
	return this->totalStats.tm;
}

//---------------------------------------------------------------------------------------

bool Engine::play(sf::RenderWindow & window,Level * levelChosen)
{
	NextLevel * next = new NextLevel(this->currentLevel);
	delay.restart().asSeconds();

	while (delay.getElapsedTime().asSeconds() < WAIT_TIME)
	{
		next->draw(window);
	}

	delete next;

	// Je¿eli uda³o siê rozegraæ poziom
	if (levelChosen->play(window, this->hero))
	{
		// Zaktualizuj wyniki
		this->totalStats.pts = levelChosen->getPoints();
		this->totalStats.tm = levelChosen->getTime();
		this->currentLevel++;
		return true;
	}
	// Je¿eli nie uda³o siê rozegraæ poziomu
	else
	{
		// Zaktualizuj wyniki
		this->totalStats.pts = levelChosen->getPoints();
		this->totalStats.tm = levelChosen->getTime();
		return false;
	}
}

//---------------------------------------------------------------------------------------

void Engine::run(sf::RenderWindow & window)
{
	this->running = true;

	for (int i = 0; i < this->totalLevels; ++i)
	{
		if (this->play(window, levels[currentLevel - 1]) == false)
		{
			break;
		}
	}

	this->running = false;
}

//---------------------------------------------------------------------------------------