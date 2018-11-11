#ifndef SPELL_H_
#define SPELL_H_

#define SPELL_COOLDOWN 1

class Spell : public Moveable
{
protected:
	int manaCost; // Koszt many czaru
	int power; // Si³a czaru
	float speed; // Prêdkoœæ z jak¹ porusza siê czar
	float distance; // Aktualnie przebyty dystans przez czar
	float maxDistance; // Maksymalna odleg³oœæ jak¹ mo¿e przebyæ czar
	bool isMovingRight; // Flaga okreœlaj¹ca w któr¹ stronê poziomo porusza siê czar

	Animation animation; // Animacja czaru
	bool first, second, third; // Stadia rozwoju animacji czaru
	int row; // Aktualnie wyœwietlany rz¹d animacji
	sf::Vector2f startingPos; // Wspó³rzêdne nadawane podczas rzucania czaru

public:
	Spell();
	virtual ~Spell();

	void setDirection(bool); // Ustawia kierunek poruszania siê czaru
	void setStartingPos(sf::Vector2f); // Ustawia wspó³rzêdne pocz¹tkowe czaru
	bool getDirection(); // Pobiera kierunek, w którym porusza siê czar

	virtual void draw(sf::RenderWindow &); // Rysuje czar
	virtual bool collision(Entity *); // Reakcja czaru na zderzenie z obiektami
	virtual void update(float); // AKtualizacja czaru
};

//---------------------------------------------------------------------------------------

// Klasa kuli ognia
class Fireball : public Spell
{
public:
	Fireball();
	~Fireball();
};

//---------------------------------------------------------------------------------------

// Klasa kuli zimna
class Frostbolt : public Spell
{
public:
	Frostbolt();
	~Frostbolt();
};

//---------------------------------------------------------------------------------------

// Klasa kuli ciemnoœci
class Shadowbolt : public Spell
{
public:
	Shadowbolt();
	~Shadowbolt();
};

//---------------------------------------------------------------------------------------

#endif