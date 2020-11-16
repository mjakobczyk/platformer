#ifndef GAME_H_
#define GAME_H_

// GameState represents possible states that application can be in.
enum GameState
{
	MENU = 0,
	GAME = 1,
	END = 2
};

// Game is a singleton that manages main application flow.
class Game
{
public:
	inline static const std::string GAME_NAME = "Platformer";

	void run();
	void updateScore(int, float);

	sf::RenderWindow &getWindow();
	GameState getState();
	void setState(GameState);

	Game();
	~Game();

protected:
	sf::RenderWindow window;
	GameState state;
	int lastPoints;
	float lastTime;
};

#endif
