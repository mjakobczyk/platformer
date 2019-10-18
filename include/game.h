#ifndef GAME_H_
#define GAME_H_

// GameState represents possible states that application can be in.
enum GameState { MENU = 0, GAME = 1, END = 2};

// Game is a singleton that manages main application flow.
class Game
{
protected:
	sf::RenderWindow window; // Okno, w kt�rym b�dzie wy�wietlana ca�a gra
	GameState state; // Stan, w kt�rym aktualnie znajduje si� gra
	int lastPoints; // Przechowuje informacje o ostatnich zdobytych punktach gracza
	float lastTime; // Przechowuje informacje o ostatnim czasie gry

public:
	Game();
	~Game();

	sf::RenderWindow & getWindow(); // Zwraca uchwyt do oryginalnego okna gry
	GameState getState(); // Zwraca aktualny stan, w kt�rym znajduje si� gra
	void setState(GameState); // Ustawia stan gry na podstawie maszyny stanu

	void run(); // Powoduje rozruch gry, wywo�uje si� z poziomu maina
	void updateScore(int, float); // Aktualizuje wynik ostatniej gry
};

#endif
