#ifndef ENTITY_H_
#define ENTITY_H_

// Klasa jednostki, okreœla jak ma wygl¹d pojedynczy element gry
class Entity
{
protected:
	bool dead; // Okreœla czy dana jednostka mo¿e funkcjonowaæ w grze
	bool canMove; // Okreœla czy dana jednostka mo¿e siê poruszaæ
	int ID; // Nadaje jednostce numer do przysz³ej ewentualnej identyfikacji

	sf::Clock clock; // S³u¿y do odmierzania czasu miêdzy interakcjami
	sf::Texture * texture; // WskaŸnik na teksturê postaci
	sf::Sprite sprite; // Do niego ³adowana jest tekstura
	sf::Vector2i coords; // Okresla aktualn¹ pozycjê jednostki w wersji kafelkowej
	sf::Vector2f coordsFlt; // Okreœla aktualn¹ pozycjê jednostki w wersji rzeczywistej

public:
	Entity();
	virtual ~Entity();

	int getID() { return this->ID; } // Zwracana identyfikator jednostki
	sf::Clock getClock() { return this->clock; }
	sf::Texture * getTexture() { return this->texture; } // Zwraca wskaŸnik na teksturê jendostki
	sf::Sprite getSprite() { return this->sprite; } // Zwraca sprite jednostki
	sf::Vector2i getCoords(); // Zwraca pozycjê jednostki w wersji kafelkowanej
	sf::Vector2f getPosition(); // Zwraca rzeczywist¹ pozycjê jednostki

	void setTexture(sf::Texture*); // Ustawia teksturê jednostki
	void setPosition(sf::Vector2f); // Ustawia pozycjê jednostki
	void setCoords(sf::Vector2i); // Ustawia kafelkow¹ pozycjê jednostki

	bool isStable(); // Sprawdza, czy jednostka jest jednostk¹ sta³¹
	bool isMoveable(); // Sprawdza, czy jednostka jest jednostk¹ dynamiczn¹
	bool isDead(); // Sprawdza, czy jednostka mo¿e byæ na mapie
	bool destroy(); // Niszczy obiekt

	virtual bool checkCollision(Entity *); // Sprawdza kolizje z inn¹ jednostk¹, mo¿e wygl¹daæ ró¿nie dla klas potomnych
	virtual bool collision(Entity *) = 0; // Okreœla co siê dzieje podczas kolizji
	virtual void update(float) = 0; // Sposób aktualizacji jednostki
};

#endif