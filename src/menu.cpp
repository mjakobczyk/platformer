#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Menu::Menu()
{
	// Za³adowanie wykorzystywanej czcionki
	if (!font.loadFromFile("Czcionki/blockss.otf")) // "Czcionki/blockss.otf"
	{
		std::cout << "Blad odczytu czcionki!" << std::endl;
		return;
	}

	// Inicjalizacja zmiennych odpowiedzialnych za poruszanie siê po menu
	buttonId = 0;
	deltaTime = 0.1f;
	heroSpecSet = false;
	menuState = MAIN_MENU;
}

//---------------------------------------------------------------------------------------

Menu::~Menu()
{
	;
}

//---------------------------------------------------------------------------------------

bool Menu::isSpecSet()
{
	if (heroSpecSet)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------------------------------------

heroSpec Menu::getChosenSpec()
{
	if (this->isSpecSet()) return whichSpecSet;
	else return heroSpec::unknown;
}

//--------------------------------------------------------------------------------------

int Menu::getButtonId()
{ 
	return this->buttonId; 
}

//---------------------------------------------------------------------------------------

sf::Font Menu::getFont() 
{ 
	return this->font;
}

//---------------------------------------------------------------------------------------

MenuState Menu::getMenuState()
{ 
	return this->menuState; 
}

//---------------------------------------------------------------------------------------

void Menu::setMenuState(MenuState new_menuState) 
{ 
	this->menuState = new_menuState; 
}

//---------------------------------------------------------------------------------------

void Menu::moveUp()
{
	if (buttonId - 1 >= 0)
	{
		buttons[buttonId]->setColor(sf::Color::White);
		buttonId--;
		buttons[buttonId]->setColor(sf::Color::Red);
	}
}

//---------------------------------------------------------------------------------------

void Menu::moveDown(int maxNumber)
{
	if (buttonId + 1 < maxNumber)
	{
		buttons[buttonId]->setColor(sf::Color::White);
		buttonId++;
		buttons[buttonId]->setColor(sf::Color::Red);
	}
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

MainMenu::MainMenu()
{
	for (int i = 0; i < MAIN_MENU_BUTTONS_QUANTITY; ++i)
	{
		Button * tmp = new Button;
		tmp->setFont(Menu::font);
		tmp->setColor(sf::Color::White);
		tmp->setSize(100);
		switch (i)
		{
		case 0: tmp->setName("Play"); break;
		case 1: tmp->setName("Options"); break;
		case 2: tmp->setName("Exit"); break;
		default: break;
		}
		tmp->setPos(sf::Vector2f(static_cast<float>(WIDTH - tmp->getText().getGlobalBounds().width) / 2, 
								 static_cast<float>(HEIGHT / (MAIN_MENU_BUTTONS_QUANTITY + 1) + i * 125)));
		buttons.push_back(tmp);
	}

	buttons[0]->setColor(sf::Color::Red);
	backgroundT.loadFromFile("Grafiki/backg1.jpg"); // "Grafiki/map_01.png"
	backgroundS.setTexture(backgroundT);
	backgroundS.setScale(1, 1);
	menuState = MAIN_MENU;
}

//---------------------------------------------------------------------------------------

MainMenu::~MainMenu()
{
	for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		if (*it != nullptr)
			delete (*it);
	}
}

//---------------------------------------------------------------------------------------

void MainMenu::run(sf::RenderWindow & whichWindow)
{
	while (whichWindow.isOpen() && this->getMenuState() == MAIN_MENU)
	{
		sf::Event event;

		while (whichWindow.pollEvent(event))
		{
			switch (event.type)	
			{
			case sf::Event::Closed:
			{
				whichWindow.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
				{
					this->moveUp();
					break;
				}
				case sf::Keyboard::A:
				case sf::Keyboard::Left:
				{
					break;
				}
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
				{
					this->moveDown(MAIN_MENU_BUTTONS_QUANTITY);
					break;
				}
				case sf::Keyboard::D:
				case sf::Keyboard::Right:
				{
					break;
				}
				case sf::Keyboard::Return:
				{
					switch (this->getButtonId())
					{
					case 0: { std::cout << "Play button has been pressed!" << std::endl; 
						this->setMenuState(MenuState::PLAY); return; } // menuState = PLAY; 
					case 1: { std::cout << "Options button has been pressed!" << std::endl; 
						break; } // menuState = OPTIONS;
					case 2: { std::cout << "Exit button has been pressed!" << std::endl;
						this->setMenuState(MenuState::EXIT); return; } // menuState = END;
					default: break;
					}
					break;
				}
				case sf::Keyboard::Escape: { std::cout << "Escape has been pressed!" << std::endl; return; break; }
				default: { std::cout << "Unknown key!" << std::endl; break; }
				}
			default:
				break;
			}
			}
		}

		whichWindow.clear();
		this->draw(whichWindow);
		whichWindow.display();
	}
}

//---------------------------------------------------------------------------------------

void MainMenu::draw(sf::RenderWindow & whichWindow)
{
	whichWindow.draw(backgroundS);

	for (int i = 0; i < MAIN_MENU_BUTTONS_QUANTITY; ++i)
	{
		buttons[i]->draw(whichWindow);
	}
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

Play::Play()
{
	for (int i = 0; i < PLAY_BUTTONS_QUANTITY; ++i)
	{
		Button * tmp = new Button;
		tmp->setFont(Menu::font);
		tmp->setColor(sf::Color::White);
		tmp->setSize(60);
		switch (i)
		{
		case 0: {
			tmp->setName("1. Choose your class:");
			tmp->setColor(sf::Color::Blue);
			tmp->setSize(100);
			tmp->setPos(sf::Vector2f((WIDTH - tmp->getText().getGlobalBounds().width) / 2, 125));
			break;
		}
		case 1: tmp->setName("Warlock"); break;
		case 2: tmp->setName("Mage"); break;
		case 3: tmp->setName("Priest"); break;
		case 4: {
			tmp->setName("<< Return <<");
			tmp->setColor(sf::Color::White);
			tmp->setSize(25);
			tmp->setPos(sf::Vector2f((WIDTH - tmp->getText().getGlobalBounds().width) / 2, HEIGHT - 124));
			break;
		}
		default: break;
		}

		tmp->setPos(sf::Vector2f(static_cast<float>(WIDTH - tmp->getText().getGlobalBounds().width) / 2,
								 static_cast<float>(HEIGHT / (MAIN_MENU_BUTTONS_QUANTITY - 124) + i * 125)));
		buttons.push_back(tmp);
	}

	buttonId = 1; // Ustawienie domyœlnego przycisku na pierwszy poza tytu³owym
	buttons[1]->setColor(sf::Color::Red); // Podœwietlony na czerwono bêdzie przycisk pod tytu³em
	heroSpecSet = false;
	backgroundT.loadFromFile("Grafiki/backg1.jpg"); // "Grafiki/map_01.png"
	backgroundS.setTexture(backgroundT);
	backgroundS.setScale(1, 1);
	this->setMenuState(PLAY);
}

//---------------------------------------------------------------------------------------

Play::~Play()
{
	for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		if (*it != nullptr)
			delete (*it);
	}
}

//---------------------------------------------------------------------------------------

void Play::moveUp()
{
	if (buttonId - 1 >= 1)
	{
		buttons[buttonId]->setColor(sf::Color::White);
		buttonId--;
		buttons[buttonId]->setColor(sf::Color::Red);
	}
}

//---------------------------------------------------------------------------------------

void Play::moveDown(int maxNumber)
{
	if (buttonId + 1 < maxNumber)
	{
		buttons[buttonId]->setColor(sf::Color::White);
		buttonId++;
		buttons[buttonId]->setColor(sf::Color::Red);
	}
}

//---------------------------------------------------------------------------------------

void Play::run(sf::RenderWindow & whichWindow)
{
	while (whichWindow.isOpen() && this->getMenuState() == PLAY)
	{
		sf::Event event;

		while (whichWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				whichWindow.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
				{
					this->moveUp();
					break;
				}
				case sf::Keyboard::A:
				case sf::Keyboard::Left:
				{
					break;
				}
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
				{
					this->moveDown(PLAY_BUTTONS_QUANTITY);
					break;
				}
				case sf::Keyboard::D:
				case sf::Keyboard::Right:
				{
					break;
				}
				case sf::Keyboard::Return:
				{
					switch (this->getButtonId())
					{
					case 0: { std::cout << "1st button has been pressed!" << std::endl; break; } // menuState = 
					case 1: { std::cout << "Warlock specialization has been chosen!" << std::endl;
						whichSpecSet = heroSpec::warlock; heroSpecSet = true; break; } // menuState = 
					case 2: { std::cout << "Mage specialization has been chosen!" << std::endl;
						whichSpecSet = heroSpec::mage; heroSpecSet = true; moveUp();  break; } // menuState = 
					case 3: { std::cout << "Priest specialization has been chosen!!" << std::endl;
						whichSpecSet = heroSpec::priest; heroSpecSet = true; moveUp(); moveUp(); break; } // menuState = 
					case 4: { std::cout << "Return button has been pressed!" << std::endl; 
						this->setMenuState(MAIN_MENU); moveUp(); moveUp(); moveUp(); return; } // Przy ustawianiu stanu musi byæ return;
					default: break;
					}
					break;
				}
				case sf::Keyboard::Escape: { std::cout << "Escape has been pressed!" << std::endl; return; break; }
				default: { std::cout << "Unknown key!" << std::endl; break; }
				}
			default:
				break;
			}
			}
		}

		if (heroSpecSet) { 
			this->setMenuState(MAIN_MENU);
		}

		whichWindow.clear();
		this->draw(whichWindow);
		whichWindow.display();
	}
}

//---------------------------------------------------------------------------------------

void Play::draw(sf::RenderWindow & whichWindow)
{
	whichWindow.draw(backgroundS);

	for (int i = 0; i < PLAY_BUTTONS_QUANTITY; ++i)
	{
		buttons[i]->draw(whichWindow);
	}
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

Options::Options()
{
	;
}

//---------------------------------------------------------------------------------------

Options::~Options()
{
	;
}

//---------------------------------------------------------------------------------------

void Options::run(sf::RenderWindow & whichWindow)
{

}

//---------------------------------------------------------------------------------------

void Options::draw(sf::RenderWindow & whichWindow)
{
	;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

NextLevel::NextLevel(int number)
{
	for (int i = 0; i < NEXT_LEVEL_BUTTONS_QUANTITY; ++i)
	{
		Button * tmp = new Button;
		tmp->setFont(Menu::font);
		tmp->setColor(sf::Color::White);
		tmp->setSize(100);
		switch (i)
		{
		case 0: 
		{
			tmp->setName("Level " + convertIntToString(number));
			tmp->setColor(sf::Color::Blue);
			tmp->setSize(100);
			break;
		}
		case 1:
		{
			switch (number)
			{
			case 1:
			{
				tmp->setName("You are not prepared!");
				tmp->setColor(sf::Color::White);
				tmp->setSize(100);

				for (int i = 0; i < 10; ++i)
				{
					Villain * villain = new Villain;
					villain->setPosition(sf::Vector2f(static_cast<float>(1800 - 80 * i), 1200));
					villain->setSize(sf::Vector2f(3.0f, 3.0f));
					visualisation.push_back(villain);
				}

				break;
			}
			case 2:
			{
				tmp->setName("Dont you want to give up?");
				tmp->setColor(sf::Color::White);
				tmp->setSize(100);

				for (int i = 0; i < 5; ++i)
				{
					Zombie * zombie = new Zombie;
					zombie->setSize(sf::Vector2f(3.0f, 3.0f));
					zombie->setPosition(sf::Vector2f(static_cast<float>(1400 - 80 * i), 1200));
					zombie->setEndPos(sf::Vector2f(1600, 1200));
					zombie->setBackPos(sf::Vector2f(1200, 1200));
					visualisation.push_back(zombie);
				}

				break;
			}
			case 3:
			{
				tmp->setName("Do you feel... stressed?");
				tmp->setColor(sf::Color::White);
				tmp->setSize(100);

				for (int i = 0; i < 10; ++i)
				{
					if (i < 5)
					{
						Zombie * zombie = new Zombie;
						zombie->setSize(sf::Vector2f(3.0f, 3.0f));
						zombie->setPosition(sf::Vector2f(static_cast<float>(1100 - 80 * i), 1125));
						zombie->setStartPos(sf::Vector2f(static_cast<float>(1100 - 80 * i), 1125));
						zombie->setEndPos(sf::Vector2f(1600, 1125));
						zombie->setBackPos(sf::Vector2f(800, 1125));
						visualisation.push_back(zombie);
					}
					else
					{
						Villain * villain = new Villain;
						villain->setDirection(false);
						villain->setPosition(sf::Vector2f(static_cast<float>(2100 - 120 * i / 2), 1200));
						villain->setSize(sf::Vector2f(3.0f, 3.0f));
						visualisation.push_back(villain);
					}
				}

				break;
			}
			default:
				break;
			}
			break;
		}
		default: break;
		}


		tmp->setPos(sf::Vector2f(static_cast<float>(WIDTH - tmp->getText().getGlobalBounds().width) / 2, 
								 static_cast<float>(HEIGHT / (MAIN_MENU_BUTTONS_QUANTITY - 124) + i * 125)));
		buttons.push_back(tmp);
	}

	backgroundT.loadFromFile("Grafiki/backg1.jpg"); // "Grafiki/map_01.png"
	backgroundS.setTexture(backgroundT);
	backgroundS.setScale(1, 1);

	deltaTime = 0.02f;
	this->setMenuState(NEXT);
}

//---------------------------------------------------------------------------------------

NextLevel::~NextLevel()
{
	for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		if (*it != nullptr)
			delete (*it);
	}

	for (std::vector<Enemy*>::iterator it = visualisation.begin(); it != visualisation.end(); ++it)
	{
		if (*it != nullptr)
			delete (*it);
	}
}

//---------------------------------------------------------------------------------------

void NextLevel::run(sf::RenderWindow & whichWindow)
{
	while (whichWindow.isOpen() && this->getMenuState() == NEXT)
	{
		this->draw(whichWindow);
	}
}

//---------------------------------------------------------------------------------------

void NextLevel::draw(sf::RenderWindow & whichWindow)
{
	whichWindow.clear();
	whichWindow.draw(backgroundS);

	// Wypisanie napisów
	for (int i = 0; i < NEXT_LEVEL_BUTTONS_QUANTITY; ++i)
	{
		buttons[i]->draw(whichWindow);
	}

	// Aktualizacja efektów
	for (std::vector<Enemy*>::iterator it = visualisation.begin(); it != visualisation.end(); ++it)
	{
		if (*it == nullptr) continue;

		(*it)->update(this->deltaTime);
	}

	// Wyœwietlenie dodatkowych efektów
	for (std::vector<Enemy*>::iterator it = visualisation.begin(); it != visualisation.end(); ++it)
	{
		(*it)->draw(whichWindow);
	}

	whichWindow.display();
}

//---------------------------------------------------------------------------------------

EndGame::EndGame(int pts, float tm)
{
	for (int i = 0; i < ENDGAME_BUTTONS_QUANTITY; ++i)
	{
		Button * tmp = new Button;
		tmp->setFont(Menu::font);
		tmp->setColor(sf::Color::White);
		tmp->setSize(100);

		switch (i)
		{
		case 0:
		{
			tmp->setName("> WALL OF JUSTICE<");
			tmp->setColor(sf::Color::Red);
			tmp->setSize(60);
			tmp->setPos(sf::Vector2f((WIDTH - tmp->getText().getGlobalBounds().width) / 2, 300));
			break;
		}
		case 1:
		{
			tmp->setName("Points: " + convertIntToString(pts));
			tmp->setColor(sf::Color::Red);
			tmp->setSize(60);
			tmp->setPos(sf::Vector2f((WIDTH - tmp->getText().getGlobalBounds().width) / 2, 400));
			break;
		}
		case 2:
		{
			tmp->setName("Time: " + convertSecondsToMinutes(tm));
			tmp->setColor(sf::Color::Red);
			tmp->setSize(60);
			tmp->setPos(sf::Vector2f((WIDTH - tmp->getText().getGlobalBounds().width) / 2, 500));
			break;
		}
		case 3:
		{
			tmp->setName("Return");
			tmp->setColor(sf::Color::Red);
			tmp->setSize(60);
			tmp->setPos(sf::Vector2f((WIDTH - tmp->getText().getGlobalBounds().width) / 2, 600));
			break;
		}
		default: 
			break;
		}

		buttons.push_back(tmp);
	}

	GameOver * gameover = new GameOver;
	gameover->setPosition(sf::Vector2f((WIDTH - gameover->getSprite().getGlobalBounds().width )/ 2, 100));
	stableObjects.push_back(gameover);
	buttons[0]->setColor(sf::Color::Red);
	backgroundT.loadFromFile("Grafiki/backg1.jpg"); // "Grafiki/map_01.png"
	backgroundS.setTexture(backgroundT);
	backgroundS.setScale(1, 1);
	menuState = MenuState::GAME_OVER;

	deltaTime = 0.2f;
	buttonId = 3;
}

//---------------------------------------------------------------------------------------

EndGame::~EndGame()
{
	for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		if (*it == nullptr) continue;

		delete *it;
	}

	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		delete *it;
	}
}

//---------------------------------------------------------------------------------------

void EndGame::run(sf::RenderWindow & whichWindow)
{
	while (whichWindow.isOpen() && this->getMenuState() == GAME_OVER)
	{
		this->draw(whichWindow);

		sf::Event event;

		while (whichWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				whichWindow.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
				{
					switch (this->getButtonId())
					{
					case 3: { std::cout << "Coming back to Main Menu!" << std::endl;
						this->setMenuState(MenuState::MAIN_MENU); break; }
					default: break;
					}
					break;
				}
				case sf::Keyboard::Escape: { std::cout << "Escape has been pressed!" << std::endl; return; break; }
				default: { std::cout << "Unknown key!" << std::endl; break; }
				}
			default:
				break;
			}
			}
		}
	}
}

//---------------------------------------------------------------------------------------

void EndGame::draw(sf::RenderWindow & whichWindow)
{
	whichWindow.clear();
	whichWindow.draw(backgroundS);

	// Wypisanie przycisków
	for (std::vector<Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		if (*it == nullptr) continue;

		(*it)->draw(whichWindow);
	}

	// Aktualizacja efektów
	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		if (*it == nullptr) continue;

		(*it)->update(this->deltaTime);
	}

	// Wyœwietlenie dodatkowych efektów
	for (std::vector<Stable*>::iterator it = stableObjects.begin(); it != stableObjects.end(); ++it)
	{
		(*it)->draw(whichWindow);
	}

	whichWindow.display();
}

//---------------------------------------------------------------------------------------