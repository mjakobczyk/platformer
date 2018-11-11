#pragma once
#include "stable.h"

// Klasa obiektu wyœwietlanego na zakoñczenie gry
class GameOver : public Stable
{
	float totalTime; // Ca³kowity czas zmiany tekstury, nie mo¿e przekraczaæ switch time'u
	float switchTime; // Okreœla czêstoœæ zmian tekstury postaci
	int row; // Okreœla w którym rzêdzie animacji jesteœmy

	sf::Clock clock; // Czas dzia³ania
	Animation animation; // Animacja obiektu
	bool down; // Flaga czy animacja pobiera kolejne klatki w dó³

public:
	GameOver();
	virtual ~GameOver();

	virtual void update(float) final; // Aktualizacja obiektu
};

