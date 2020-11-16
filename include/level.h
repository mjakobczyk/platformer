#ifndef LEVEL_H_
#define LEVEL_H_

#define STARTING_LEVEL_NUMBER 1
#define LEVELS_QUANTITY 2
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

class Stats
{
public:
	int pts;
	float tm;

	Stats() : pts(0), tm(0) {};
	~Stats() {};
};

// Klasa poziomu gry
class Level
{
	static int points;
	static float time;

protected:
	int width; // Szeroko�� poziomu
	int height; // Wysoko�� poziomu
	int visibleWidth; // Widoczna szeroko�� poziomu
	int visibleHeight; // Widoczna wysoko�� poziomu
	short levelNumber; // Numer poziomu
	float startX; // Wsp�rz�dna X rozpocz�cia gry dla gracza
	float startY; // Wsp�rz�dna Y rozpocz�cia gry dla gracza
	float totalTime; // Ca�kowity czas rozgrywki
	float switchTime; // Maksymalny czas zmiany pomi�dzy klatkami wy�wietlanych obiekt�w
	float delta; // R�nica w czasie pomi�dzy klatkami
	bool isActive; // Flaga okre�laj�ca czy poziom jest grany
	bool isCompleted; // Flaga okre�laj�ca czy poziom zosta� zako�czony

	std::string levelName; // Nazwa poziomu
	std::vector <sf::Texture*> textures; // Wektor 1d dost�pnych tekstur
	std::vector <Stable*> stableObjects; // Wektor 1d obiekt�w sta�ych
	std::vector <Moveable*> moveableObjects; // Wektor 1d obiekt�w poruszaj�cych si�
	std::vector <std::vector <sf::Sprite>> sprites; // Wektor 2d wy�wietlanych sprite'�w
	std::vector <std::vector <Tile>> tiles; // Wektor 2d kafli w postaci numerycznej
	std::vector <Tile*> obstacles; // Wektor 1d przeszk�d
	std::vector <Enemy*> enemies; // Wektor 1d przeciwnik�w
	std::vector <Spell*> spells; // Wektor 1d czar�w

	sf::View camera; // Kamera, kt�ra wy�wietla aktua
	sf::Clock clock; // G��wny zegar gry
	sf::Texture backgroundT; // Tekstura t�a
	sf::Sprite backgroundS; // Sprite t�a

	sf::RenderWindow & window; // Uchwyt do oryginalnego okna gry
	Hero *& hero; // Uchwyt do oryginalnego gracza
	Spell * spell; // Wska�nik na aktualnie rzucany czar
	Interface interface; // Wy�wietlany interfejs gry

public:
	Level(sf::RenderWindow &, Hero *&);
	virtual ~Level();

	void setLevelSize(unsigned int, unsigned int); // Ustawia wielko�� poziomu
	void setLevelNumber(unsigned short); // Ustawia numer poziomu
	void setLevelName(const std::string &); // Ustawia nazw� poziomu
	void setLevelBackGround(sf::Texture *); // Ustawia t�o poziomu
	void setLevel(sf::RenderWindow &, const std::string &); // Ustawia rodzaj poziomu

	void resetPoints(); // Resetuje uzyskan� ilo�� punkt�w
	void resetTime(); // Resetuje czas przebytych poziom�w	

	sf::Time getCurrentTime(); // Pobiera aktualny czas gry
	sf::Vector2i checkCollisions(Entity *, Direction); // Sprawdza kolizje w danym kierunku
	int getPoints(); // Pobiera ilo�� punkt�w uzyskanych podczas gry
	float getTime(); // Pobiera czas przebytych poziom�w
	void awardPoint(int); // Nadaje punkt za uzyskanie bonusu

	void updateLevel(float); // Od�wie�a map� poziomu
	void checkCollisions(); // Sprawdza kolizje pomi�dzy obiektami
	void update(); // Aktualizuje wszystkie elementy poziomu
	void draw(); // Rysuje wszystkie elementy poziomu

	virtual bool play(sf::RenderWindow &, Hero *&); // Pozwala zagra� w poziom

private:
	bool loadFromFile(const std::string &); // �aduje informacje o poziomie z pliku
};

//---------------------------------------------------------------------------------------

class Level_01 : public Level
{

public:
	Level_01(sf::RenderWindow &, Hero *&);
	virtual ~Level_01();

	/*virtual void play(sf::RenderWindow &, Hero *&) final;
	virtual void draw(sf::RenderWindow &, Hero *&) final;*/
};

//---------------------------------------------------------------------------------------

class Level_02 : public Level
{

public:
	Level_02(sf::RenderWindow &, Hero *&);
	virtual ~Level_02();

	//virtual void play(sf::RenderWindow &, Hero *&) final;
	//virtual void draw(sf::RenderWindow &, Hero *&) final;
};

//---------------------------------------------------------------------------------------
#endif