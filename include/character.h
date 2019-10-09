#ifndef CHARACTER_H_
#define CHARACTER_H_

enum Direction { UNKNOWN = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };

#define MIN_HEALTH 1
#define MAX_HEALTH 10

// Klasa postaci
class Character : public Moveable
{
protected:
	// Zmienne okre�laj�ce imi� i atrybuty postaci
	std::string name;
	int health, mana;
	
	sf::Vector2f movement; // Okre�la pr�dko�� postaci w uk�adzie kartezja�skim
	sf::Vector2f lastMovement; // Zapisuje warto�� ostatnio poczynionego ruchu
	Animation animation; // Animacja postaci
	Direction lastDirection; // Zapisuje w kt�rym kierunku nast�pi� ostatni ruch
	unsigned int row; // Okre�la �adowany rz�d w teksturze animacji
	float tempDelta; // Czas efektu oddzia�uj�cego na posta�
	float moveSpeed; // Okre�la pr�dko�� ruchu postaci
	float jumpSpeed; // Okre�la pr�dko�� skoku postaci
	float gravity; // Grawitacja wsp�pracuje ze skokami postaci
	float offset; // Okre�la jak daleki skok wykonany
	float groundHeight; // Okre�la poziom gruntu mapy, jednakowy wsz�dzie
	// Okre�laj� czy posta� jest zwr�cona w danym kierunku, czy skacze, czy spada
	// i czy z czym� aktualnie koliduje
	bool faceRight, isJumping, isFalling, isColliding; 
	bool debuffActive; // Okre�la czy na gracza jest na�o�ony jaki� efekt
	bool pendingSpell; // Okre�la czy gracz mo�e rzuca� zakl�cie

public:
	// Zmienne okre�laj�ce czy posta� mo�e porusza� si� w danym kierunku
	bool canMoveRight, canMoveLeft, canJump, canFall;

public:
	Character();
	Character(sf::Texture*);
	Character(sf::Vector2u, float);
	Character(sf::Texture*, sf::Vector2u, float);
	virtual  ~Character();

	int getHealth(); // Zwraca aktualn� ilo�� zdrowia postaci
	Direction getLastDirection(); // Pobiera ostatni obrany kierunek
	sf::Vector2f getLastMovement();; // Pobiera ostatni ruch
	
	void setX(float); // Ustawia wsp�rz�dn� X pozycji postaci
	void setY(float); // Ustawia wsp�rz�dn� Y pozycji postaci
	void setName(const std::string &); // Ustawia imie postaci
	void setHealth(int); // Ustawia zdrowie postaci
	void setMana(int); // Ustawia mane postaci
	void setDirection(bool); // Ustawia kierunek zwrotu postaci
	void setCollisionState(bool); // Ustawia czy gracz na co� napotka�

	bool isFacingRight(); // Sprawdza, czy posta� porusza si� w prawo
	bool isSpellPending(); // Sprawdza, czy wyra�ono ch�� u�ycia czaru
	void move(sf::Vector2f); // Zmienia pozycj� postaci o zadan� warto��
	void slow(float); // Spowalnia bohatera na dany czas
	void hurt(float); // Zadaje graczowi obra�enia
	
	virtual void draw(sf::RenderWindow &);
	virtual bool collision(Entity *);
	virtual void update(float);
};

#endif