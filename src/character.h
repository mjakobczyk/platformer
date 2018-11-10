#ifndef CHARACTER_H_
#define CHARACTER_H

enum Direction { UNKNOWN = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };

#define MIN_HEALTH 1
#define MAX_HEALTH 10

// Klasa postaci
class Character : public Moveable
{
protected:
	// Zmienne okreœlaj¹ce imiê i atrybuty postaci
	std::string name;
	int health, mana;
	
	sf::Vector2f movement; // Okreœla prêdkoœæ postaci w uk³adzie kartezjañskim
	sf::Vector2f lastMovement; // Zapisuje wartoœæ ostatnio poczynionego ruchu
	Animation animation; // Animacja postaci
	Direction lastDirection; // Zapisuje w którym kierunku nast¹pi³ ostatni ruch
	unsigned int row; // Okreœla ³adowany rz¹d w teksturze animacji
	float tempDelta; // Czas efektu oddzia³uj¹cego na postaæ
	float moveSpeed; // Okreœla prêdkoœæ ruchu postaci
	float jumpSpeed; // Okreœla prêdkoœæ skoku postaci
	float gravity; // Grawitacja wspó³pracuje ze skokami postaci
	float offset; // Okreœla jak daleki skok wykonany
	float groundHeight; // Okreœla poziom gruntu mapy, jednakowy wszêdzie
	// Okreœlaj¹ czy postaæ jest zwrócona w danym kierunku, czy skacze, czy spada
	// i czy z czymœ aktualnie koliduje
	bool faceRight, isJumping, isFalling, isColliding; 
	bool debuffActive; // Okreœla czy na gracza jest na³o¿ony jakiœ efekt
	bool pendingSpell; // Okreœla czy gracz mo¿e rzucaæ zaklêcie

public:
	// Zmienne okreœlaj¹ce czy postaæ mo¿e poruszaæ siê w danym kierunku
	bool canMoveRight, canMoveLeft, canJump, canFall;

public:
	Character();
	Character(sf::Texture*);
	Character(sf::Vector2u, float);
	Character(sf::Texture*, sf::Vector2u, float);
	virtual  ~Character();

	int getHealth(); // Zwraca aktualn¹ iloœæ zdrowia postaci
	Direction getLastDirection(); // Pobiera ostatni obrany kierunek
	sf::Vector2f getLastMovement();; // Pobiera ostatni ruch
	
	void setX(float); // Ustawia wspó³rzêdn¹ X pozycji postaci
	void setY(float); // Ustawia wspó³rzêdn¹ Y pozycji postaci
	void setName(const std::string &); // Ustawia imie postaci
	void setHealth(int); // Ustawia zdrowie postaci
	void setMana(int); // Ustawia mane postaci
	void setDirection(bool); // Ustawia kierunek zwrotu postaci
	void setCollisionState(bool); // Ustawia czy gracz na coœ napotka³

	bool isFacingRight(); // Sprawdza, czy postaæ porusza siê w prawo
	bool isSpellPending(); // Sprawdza, czy wyra¿ono chêæ u¿ycia czaru
	void move(sf::Vector2f); // Zmienia pozycjê postaci o zadan¹ wartoœæ
	void slow(float); // Spowalnia bohatera na dany czas
	void hurt(float); // Zadaje graczowi obra¿enia
	
	virtual void draw(sf::RenderWindow &);
	virtual bool collision(Entity *);
	virtual void update(float);
};

#endif