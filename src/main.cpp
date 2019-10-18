#include "../include/basic.h"

// Entry point of the application.
int main()
{
	Game * const game = new Game();
	game->run();
	delete game;

	return 0;
}