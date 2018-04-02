#ifndef LEVEL_H_
#define LEVEL_H_

#define LEVELS_QUANTITY 1
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
	int width; // Szerokoœæ poziomu
	int height; // Wysokoœæ poziomu
	int visibleWidth; // Widoczna szerokoœæ poziomu
	int visibleHeight; // Widoczna wysokoœæ poziomu
	short levelNumber; // Numer poziomu
	float startX; // Wspó³rzêdna X rozpoczêcia gry dla gracza
	float startY; // Wspó³rzêdna Y rozpoczêcia gry dla gracza
	float totalTime; // Ca³kowity czas rozgrywki
	float switchTime; // Maksymalny czas zmiany pomiêdzy klatkami wyœwietlanych obiektów
	float delta; // Ró¿nica w czasie pomiêdzy klatkami
	bool isActive; // Flaga okreœlaj¹ca czy poziom jest grany
	bool isCompleted; // Flaga okreœlaj¹ca czy poziom zosta³ zakoñczony

	std::string levelName; // Nazwa poziomu
	std::vector <sf::Texture*> textures; // Wektor 1d dostêpnych tekstur
	std::vector <Stable*> stableObjects; // Wektor 1d obiektów sta³ych
	std::vector <Moveable*> moveableObjects; // Wektor 1d obiektów poruszaj¹cych siê
	std::vector <std::vector <sf::Sprite>> sprites; // Wektor 2d wyœwietlanych sprite'ów
	std::vector <std::vector <Tile>> tiles; // Wektor 2d kafli w postaci numerycznej
	std::vector <Tile*> obstacles; // Wektor 1d przeszkód
	std::vector <Enemy*> enemies; // Wektor 1d przeciwników
	std::vector <Spell*> spells; // Wektor 1d czarów

	sf::View camera; // Kamera, która wyœwietla aktua
	sf::Clock clock; // G³ówny zegar gry
	sf::Texture backgroundT; // Tekstura t³a
	sf::Sprite backgroundS; // Sprite t³a

	sf::RenderWindow & window; // Uchwyt do oryginalnego okna gry
	Hero *& hero; // Uchwyt do oryginalnego gracza
	Spell * spell; // WskaŸnik na aktualnie rzucany czar
	Interface interface; // Wyœwietlany interfejs gry

public:
	Level(sf::RenderWindow &, Hero *&);
	virtual ~Level();

	void setLevelSize(unsigned int, unsigned int); // Ustawia wielkoœæ poziomu
	void setLevelNumber(unsigned short); // Ustawia numer poziomu
	void setLevelName(const std::string &); // Ustawia nazwê poziomu
	void setLevelBackGround(sf::Texture *); // Ustawia t³o poziomu
	void setLevel(sf::RenderWindow &, const std::string &); // Ustawia rodzaj poziomu

	void resetPoints(); // Resetuje uzyskan¹ iloœæ punktów
	void resetTime(); // Resetuje czas przebytych poziomów	

	sf::Time getCurrentTime(); // Pobiera aktualny czas gry
	sf::Vector2i checkCollisions(Entity *, Direction); // Sprawdza kolizje w danym kierunku
	int getPoints(); // Pobiera iloœæ punktów uzyskanych podczas gry
	float getTime(); // Pobiera czas przebytych poziomów
	void awardPoint(int); // Nadaje punkt za uzyskanie bonusu

	void updateLevel(float); // Odœwie¿a mapê poziomu
	void checkCollisions(); // Sprawdza kolizje pomiêdzy obiektami
	void update(); // Aktualizuje wszystkie elementy poziomu
	void draw(); // Rysuje wszystkie elementy poziomu

	virtual bool play(sf::RenderWindow &, Hero *&); // Pozwala zagraæ w poziom

private:
	bool loadFromFile(const std::string &); // £aduje informacje o poziomie z pliku
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