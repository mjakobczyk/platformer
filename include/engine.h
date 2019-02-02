#ifndef ENGINE_H_
#define ENGINE_H_

#define WAIT_TIME 5

// Klasa silnika gry, zarz�dza wyborem aktualnego poziomu
class Engine
{
	int totalLevels; // Ca�kowita ilo�� poziom�w do przej�cia
	int currentLevel; // Numer aktualnie granego poziomu
	bool running; // Flaga okre�laj�ca czy trwa rozgrywka
	Stats totalStats; // Statystyki zwracane po wyj��iu z gry

	std::vector <Level*> levels; // Wektor granych poziom�w
	sf::Clock delay; // Op�nienie generowane w celu uzyskania przerywnik�w mi�dzy poziomami
	sf::RenderWindow & window; // Uchwyt do oryginalnego okna gry
	Hero * hero; // Wska�ik na tworzon� posta� gracza

public:
	Engine(sf::RenderWindow & window, heroSpec);
	~Engine();

	void updateScore(int); // Aktualizuje wynik ko�cowy
	void updateTime(float); // Aktualizuje czas, w kt�rym rozegrano gr�
	int getPoints(); // Pobiera ilo�� uzyskanych punkt�w
	float getTime(); // Pobiera czas, w jakim rozegrano gr�

	void run(sf::RenderWindow &); // Powoduje aktywacj� silnika gry 
	bool play(sf::RenderWindow &, Level*); // Pozwala rozegra� dany poziom
};

#endif