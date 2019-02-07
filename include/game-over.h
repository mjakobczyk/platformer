#ifndef GAMEOVER_H_
#define GAMEOVER_H_
#include "stable.h"

// Klasa obiektu wy�wietlanego na zako�czenie gry
class GameOver : public Stable
{
	float totalTime; // Ca�kowity czas zmiany tekstury, nie mo�e przekracza� switch time'u
	float switchTime; // Okre�la cz�sto�� zmian tekstury postaci
	int row; // Okre�la w kt�rym rz�dzie animacji jeste�my

	sf::Clock clock; // Czas dzia�ania
	Animation animation; // Animacja obiektu
	bool down; // Flaga czy animacja pobiera kolejne klatki w d�

public:
	GameOver();
	virtual ~GameOver();

	virtual void update(float) final; // Aktualizacja obiektu
};

#endif