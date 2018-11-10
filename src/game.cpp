#include "basic.h"

//---------------------------------------------------------------------------------------

Game::Game()
{
	window.create(sf::VideoMode(WIDTH, HEIGHT), "THE_GAME", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(FPS);

	state = GameState::MENU;
	int lastPoints = 0;
	float lastTime = 0;
}

//---------------------------------------------------------------------------------------

Game::~Game()
{
	std::cout << "Gra konczy dzialanie. Dziekuje za zagranie!" << std::endl;
}

//---------------------------------------------------------------------------------------

sf::RenderWindow & Game::getWindow()
{
	return window;
}

//---------------------------------------------------------------------------------------

GameState Game::getState()
{
	return state;
}

//---------------------------------------------------------------------------------------

void Game::setState(GameState state_)
{
	this->state = state_;
}

//---------------------------------------------------------------------------------------

// G³ówna pêtla programu
void Game::run()
{
	Menu * menu_ptr = nullptr;
	MainMenu mainMenu;
	menu_ptr = &mainMenu;

	// -------- GAMESTATE -----------
	while (state != END)
	{
		switch (this->state)
		{
			case GameState::MENU:
			{
				// -------- MENUSTATE -----------
				while (menu_ptr->getMenuState() != OUT)
				{
					switch (menu_ptr->getMenuState())
					{
					case MenuState::MAIN_MENU:
					{
						menu_ptr = &mainMenu;
						menu_ptr->setMenuState(MenuState::MAIN_MENU);
						menu_ptr->run(this->Game::getWindow());
						break;
					}
					case MenuState::PLAY:
					{
						Play * play = new Play;
						menu_ptr = play;
						menu_ptr->setMenuState(MenuState::PLAY);
						menu_ptr->run(this->Game::getWindow());
						if (menu_ptr->isSpecSet())
						{
							this->state = GameState::GAME;
							menu_ptr->setMenuState(MenuState::OUT);
						}
						break;
					}
					case MenuState::OPTIONS:
					{
						//Options * options = new Options;
						//menu_ptr = &options;
						//menu_ptr->setMenuState(OPTIONS);
						break;
					}
					case MenuState::GAME_OVER:
					{
						EndGame * endgame = new EndGame(this->lastPoints, this->lastTime);
						menu_ptr = endgame;
						menu_ptr->run(this->Game::getWindow());
						delete endgame;
						menu_ptr->setMenuState(MenuState::MAIN_MENU);
						break;
					}
					case MenuState::EXIT:
					{
						menu_ptr->setMenuState(MenuState::OUT);
						this->state = GameState::END;
						break;
					}
					default:
						break;
					}
				}

				 break;
			}

			// -------- TRYB GRY -----------
			case GameState::GAME: 
			{
				Engine * engine = new Engine(this->Game::getWindow(), menu_ptr->getChosenSpec());
				engine->run(this->Game::getWindow());
				this->updateScore(engine->getPoints(), engine->getTime());
				this->state = GameState::MENU;
				menu_ptr->setMenuState(MenuState::GAME_OVER);
				delete engine;

				break;
			}

			//  --------- TRYB WYJSCIA --------
			case GameState::END: 
			{
				std::cout << "Koniec gry!" << std::endl;
				return;
				break;
			}

			default:
				break;
		}
	}
}

//---------------------------------------------------------------------------------------

// Metoda kontroluj¹ca wystêpuj¹ce zdarzenia w grze
void Game::updateScore(int points_, float time_)
{
	this->lastPoints = points_;
	this->lastTime = time_;
}

//---------------------------------------------------------------------------------------