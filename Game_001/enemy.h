#ifndef ENEMY_H_
#define ENEMY_H_

#define ENEMIES_QUANTITY 1
#define OFFSET_MOVEMENT_4 4

class Enemy : public Character
{
protected:
	sf::Vector2f startPos; // Pozycja startowa przeciwnika
	sf::Vector2f endPos; // Pozycja koñcowa, do której przeciwnik pod¹¿a
	sf::Vector2f backPos; // Pozycja powrotu, do której kieruje siê przeciwnik po endPos

	float totalTime; // Ca³kowity czas zmiany tekstury, nie mo¿e przekraczaæ switch time'u
	float switchTime; // Okreœla czêstoœæ zmian tekstury postaci
	int imageNumber; // Numer aktualnie wyœwietlanej klatki z tekstury

public:
	Enemy();
	Enemy(sf::Vector2u, float);
	Enemy(sf::Texture *, sf::Vector2u, float);
	virtual ~Enemy();

	void setStartPos(sf::Vector2f); // Ustawia pozycje startow¹
	void setEndPos(sf::Vector2f); // Ustawia pozycjê koñcow¹
	void setBackPos(sf::Vector2f); // Ustawia pozycjê powrotu
	void setSize(sf::Vector2f); // Ustawia wielkoœæ przeciwnika
	void setDirection(bool); // Ustawia kierunek, w którym ma siê poruszaæ
	void setMoveSpeed(float); // Ustawia prêdkoœæ poruszania siê przeciwnika

	sf::Vector2f getStartPos(); // Pobiera pozycjê startow¹ przeciwnika
	sf::Vector2f getEndPos(); // Pobiera pozycjê koñcow¹ przeciwnika
	sf::Vector2f getBackPos(); // Pobiera pozycjê powrotu przeciwnika

	//virtual void update(float); // Aktualizuje dane o postaci
};

//---------------------------------------------------------------------------------------

#define ZOMBIE_BONUS 500

class Zombie : public Enemy
{
public:
	Zombie();
	Zombie(sf::Vector2u, float);
	Zombie(sf::Texture *, sf::Vector2u, float);
	~Zombie();

	virtual void update(float); // Aktualizuje dane o postaci
};

//---------------------------------------------------------------------------------------

#define VILLAIN_BONUS 100

class Villain : public Enemy
{
public:
	Villain();
	Villain(sf::Vector2u, float);
	Villain(sf::Texture *, sf::Vector2u, float);
	~Villain();

	virtual void update(float); // Aktualizuje dane o postaci
};

//---------------------------------------------------------------------------------------

#endif