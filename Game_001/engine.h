#ifndef ENGINE_H_
#define ENGINE_H

#define WAIT_TIME 5

// Klasa silnika gry, zarz¹dza wyborem aktualnego poziomu
class Engine
{
	int totalLevels; // Ca³kowita iloœæ poziomów do przejœcia
	int currentLevel; // Numer aktualnie granego poziomu
	bool running; // Flaga okreœlaj¹ca czy trwa rozgrywka
	Stats totalStats; // Statystyki zwracane po wyjœæiu z gry

	std::vector <Level*> levels; // Wektor granych poziomów
	sf::Clock delay; // OpóŸnienie generowane w celu uzyskania przerywników miêdzy poziomami
	sf::RenderWindow & window; // Uchwyt do oryginalnego okna gry
	Hero * hero; // WskaŸik na tworzon¹ postaæ gracza

public:
	Engine(sf::RenderWindow & window, heroSpec);
	~Engine();

	void updateScore(int); // Aktualizuje wynik koñcowy
	void updateTime(float); // Aktualizuje czas, w którym rozegrano grê
	int getPoints(); // Pobiera iloœæ uzyskanych punktów
	float getTime(); // Pobiera czas, w jakim rozegrano grê

	void run(sf::RenderWindow &); // Powoduje aktywacjê silnika gry 
	bool play(sf::RenderWindow &, Level*); // Pozwala rozegraæ dany poziom
};

#endif