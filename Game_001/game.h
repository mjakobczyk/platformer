#ifndef GAME_H_
#define GAME_H_

// Maszyna stanu gry
enum GameState { MENU = 0, GAME = 1, END = 2};

// Klasa gry, singleton zarz¹dzaj¹cy dzia³aniem ca³ej gry
class Game
{
protected:
	sf::RenderWindow window; // Okno, w którym bêdzie wyœwietlana ca³a gra
	GameState state; // Stan, w którym aktualnie znajduje siê gra
	int lastPoints; // Przechowuje informacje o ostatnich zdobytych punktach gracza
	float lastTime; // Przechowuje informacje o ostatnim czasie gry

public:
	Game();
	~Game();

	sf::RenderWindow & getWindow(); // Zwraca uchwyt do oryginalnego okna gry
	GameState getState(); // Zwraca aktualny stan, w którym znajduje siê gra
	void setState(GameState); // Ustawia stan gry na podstawie maszyny stanu

	void run(); // Powoduje rozruch gry, wywo³uje siê z poziomu maina
	void updateScore(int, float); // Aktualizuje wynik ostatniej gry
};

#endif GAME_H
