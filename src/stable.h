#ifndef STABLE_H_
#define STABLE_H_

enum Interaction { NONE = 0, STOP = 1, BONUS = 2, DAMAGE = 3, HEAL = 4, TELEPORT};

#define BONUS_POINTS 25

class Stable : public Entity
{
protected:
	bool collidable; // Flaga okreœlaj¹ca czy mo¿na wejœæ na obiekt
	bool interactable; // Flaga okreœlaj¹ca czy mo¿na wejœæ w interakcjê z obiektem
	Interaction interaction; // Typ wyliczeniowy okreœlaj¹cy sposób interakcji

public:
	Stable();
	virtual ~Stable();

	bool isCollidable(); // Sprawdza czy mo¿na wejœæ na obiekt
	bool isInteractable(); // Sprawdza czy mo¿na wejœæ w interakcjê z obiektem

	virtual Interaction getInteraction(); // Zwraca rodzaj interakcji

	virtual void draw(sf::RenderWindow &); // Rysuje obiekt
	virtual bool collision(Entity *); // Efekt kolizji z obiektem
	virtual void update(float); // Aktualizacja obiektu
};

//---------------------------------------------------------------------------------------

// Klasa monety, bonus w trakcie rozgrywki
class Coin : public Stable
{

public:
	Coin();
	~Coin();

	virtual bool collision(Entity *);
};

//---------------------------------------------------------------------------------------

#endif