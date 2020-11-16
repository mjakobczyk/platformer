#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Game::Game()
{
	this->window.create(sf::VideoMode(WIDTH, HEIGHT), Game::GAME_NAME, sf::Style::Close);
	this->window.setVerticalSyncEnabled(true);
	this->window.setFramerateLimit(FPS);

	this->state = GameState::MENU;
	this->lastPoints = 0.f;
	this->lastTime = 0.f;
}

//---------------------------------------------------------------------------------------

Game::~Game()
{
	this->window.clear();
	this->window.close();
}

//---------------------------------------------------------------------------------------

sf::RenderWindow &Game::getWindow()
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

void Game::run()
{
	Menu *const mainMenu = new MainMenu();
	Menu *play = nullptr;
	auto menuState = mainMenu;

	while (state != END)
	{
		switch (this->state)
		{
		case GameState::MENU:
		{
			while (menuState->getMenuState() != OUT)
			{
				switch (menuState->getMenuState())
				{
				case MenuState::MAIN_MENU:
				{
					menuState = mainMenu;
					menuState->setMenuState(MenuState::MAIN_MENU);
					menuState->run(this->Game::getWindow());
					break;
				}
				case MenuState::PLAY:
				{
					play = new Play();
					menuState = play;
					menuState->setMenuState(MenuState::PLAY);
					menuState->run(this->Game::getWindow());
					if (menuState->isSpecSet())
					{
						this->state = GameState::GAME;
						menuState->setMenuState(MenuState::OUT);
					}
					break;
				}
				case MenuState::OPTIONS:
				{
					break;
				}
				case MenuState::GAME_OVER:
				{
					EndGame *const endgame = new EndGame(this->lastPoints, this->lastTime);
					menuState = endgame;
					menuState->run(this->Game::getWindow());
					delete endgame;
					menuState->setMenuState(MenuState::MAIN_MENU);
					break;
				}
				case MenuState::EXIT:
				{
					menuState->setMenuState(MenuState::OUT);
					this->state = GameState::END;
					break;
				}
				default:
				{
					break;
				}
				}
			}

			break;
		}
		case GameState::GAME:
		{
			Engine *engine = new Engine(this->Game::getWindow(), menuState->getChosenSpec());
			engine->run(this->Game::getWindow());
			this->updateScore(engine->getPoints(), engine->getTime());
			this->state = GameState::MENU;
			menuState->setMenuState(MenuState::GAME_OVER);
			delete engine;

			break;
		}
		case GameState::END:
		{
			this->setState(GameState::END);
			break;
		}
		default:
		{
			this->setState(GameState::END);
			break;
		}
		}
	}
}

//---------------------------------------------------------------------------------------


void Game::updateScore(int points_, float time_)
{
	this->lastPoints = points_;
	this->lastTime = time_;
}

//---------------------------------------------------------------------------------------