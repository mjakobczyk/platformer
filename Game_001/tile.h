#ifndef TILE_H_
#define TILE_H_

enum TileType {
	BLANK = 0, STONE_1 = 1, BRICK_1 = 3, BRICK_2 = 4, LAVA_1 = 5, LAVA_2 = 6,
	WATER_1 = 7, ENTRANCE_DOOR = 8, EXIT_DOOR = 9, PAD_1 = 10, ALTAR_1 = 11,
	MARBLE_1 = 12
};

class Tile : public Stable
{
	TileType type; // Typ budowanego kafelka

public:
	Tile();
	virtual ~Tile();

	TileType getTileType(); // Pobiera obiekt statyczny kafelka
	Tile * getTilePointer(short); // Pobiera wskaŸnik na kafelek
	Tile getTile(short); // Pobiera kafel w zale¿noœci od numera, 
						 // metoda pomocniza dla dwóch powy¿szych metod
};

#endif