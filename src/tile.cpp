#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Tile::Tile() : Stable()
{
	type = TileType::STONE_1;
	clock.restart().asSeconds();
}

//---------------------------------------------------------------------------------------

Tile::~Tile()
{
	;
}

//---------------------------------------------------------------------------------------

TileType Tile::getTileType() 
{ 
	return this->type;
}

//---------------------------------------------------------------------------------------

Tile Tile::getTile(short tileCode)
{
	// Utworzenie nowego kafelka, inicjalizacja na podstawie przekazanego kodu
	Tile tile;
	tile.type = TileType(tileCode);
	sf::Texture * txr = new sf::Texture;
	
	// Utworzenie adekwatnego kafelka
	switch (TileType(tileCode))
	{
	case TileType::BLANK:
	{
		ID = 0;
		interaction = NONE;
		collidable = true;
		interactable = false;
		break;
	}
	case TileType::STONE_1:
	{
		ID = 1;
		txr->loadFromFile("Grafiki/stone_1.png");
		tile.sprite.setTexture(*txr);
		interaction = STOP;
		collidable = false;
		interactable = false;
		break;
	}
	case TileType::BRICK_1:
	{
		ID = 3;
		txr->loadFromFile("Grafiki/brick_1.png");
		tile.sprite.setTexture(*txr);
		interaction = STOP;
		collidable = false;
		interactable = false;
		break;
	}
	case TileType::BRICK_2:
	{
		ID = 4;
		txr->loadFromFile("Grafiki/brick_2.png");
		tile.sprite.setTexture(*txr);
		interaction = NONE;
		collidable = false;
		interactable = false;
		break;
	}
	case TileType::LAVA_1:
	{
		ID = 5;
		txr->loadFromFile("Grafiki/lava_1.png");
		tile.sprite.setTexture(*txr);
		interaction = DAMAGE;
		collidable = false;
		interactable = false;
		break;
	}
	case TileType::LAVA_2:
	{
		ID = 6;
		txr->loadFromFile("Grafiki/lava_2.png");
		tile.sprite.setTexture(*txr);
		interaction = DAMAGE;
		collidable = false;
		interactable = false;
		break;
	}
	case TileType::WATER_1:
	{
		ID = 7;
		txr->loadFromFile("Grafiki/water_1.png");
		sprite.setTexture(*txr);
		interaction = NONE;
		collidable = true;
		interactable = false;
		break;
	}
	case TileType::ENTRANCE_DOOR:
	{
		ID = 8;
		txr->loadFromFile("dngn_closed_door");
		tile.sprite.setTexture(*txr);
		interaction = TELEPORT;
		collidable = true;
		interactable = true;
		break;
	}
	case TileType::EXIT_DOOR:
	{
		ID = 9;
		txr->loadFromFile("Grafiki/dngn_altar.png");
		tile.sprite.setTexture(*txr);
		interaction = TELEPORT;
		collidable = true;
		interactable = true;
		break;
	}
	case TileType::PAD_1:
	{
		ID = 10;
		txr->loadFromFile("Grafiki/pad_1.png");
		sprite.setTexture(*txr);
		interaction = NONE;
		collidable = true;
		interactable = false;
		break;
	}
	case TileType::ALTAR_1:
	{
		ID = 11;
		txr->loadFromFile("Grafiki/dngn_altar.png");
		sprite.setTexture(*txr);
		interaction = NONE;
		collidable = true;
		interactable = false;
		break;
	}
	case TileType::MARBLE_1:
	{
		ID = 12;
		tile.texture->loadFromFile("Grafiki/marble_1.png");
		tile.sprite.setTexture(*texture);
		interaction = NONE;
		collidable = false;
		interactable = false;
		break;
	}
	default:
		break;
	}

	return tile;
}

//---------------------------------------------------------------------------------------

Tile * Tile::getTilePointer(short tileCode)
{
	// Utworzenie nowego kafelka, inicjalizacja na podstawie przekazanego kodu
	Tile * tile = new Tile;
	tile->type = TileType(tileCode);
	sf::Texture * txr = new sf::Texture;

	// Utworzenie adekwatnego kafelka
	switch (TileType(tileCode))
	{
	case TileType::BLANK:
	{
		tile->ID = 0;
		tile->interaction = NONE;
		tile->collidable = true;
		tile->interactable = false;
		break;
	}
	case TileType::STONE_1:
	{
		tile->ID = 1;
		txr->loadFromFile("Grafiki/stone_1.png");
		tile->sprite.setTexture(*txr);
		tile->interaction = STOP;
		tile->collidable = false;
		tile->interactable = false;
		break;
	}
	case TileType::BRICK_1:
	{
		tile->ID = 3;
		txr->loadFromFile("Grafiki/brick_1.png");
		tile->sprite.setTexture(*txr);
		tile->interaction = STOP;
		tile->collidable = false;
		tile->interactable = false;
		break;
	}
	case TileType::BRICK_2:
	{
		tile->ID = 4;
		txr->loadFromFile("Grafiki/brick_2.png");
		tile->sprite.setTexture(*txr);
		tile->interaction = NONE;
		tile->collidable = false;
		tile->interactable = false;
		break;
	}
	case TileType::LAVA_1:
	{
		tile->ID = 5;
		txr->loadFromFile("Grafiki/lava_1.png");
		tile->sprite.setTexture(*txr);
		tile->interaction = DAMAGE;
		tile->collidable = true;
		tile->interactable = true;
		break;
	}
	case TileType::LAVA_2:
	{
		tile->ID = 6;
		txr->loadFromFile("Grafiki/lava_2.png");
		tile->sprite.setTexture(*txr);
		tile->interaction = DAMAGE;
		tile->collidable = true;
		tile->interactable = true;
		break;
	}
	case TileType::WATER_1:
	{
		tile->ID = 7;
		txr->loadFromFile("Grafiki/water_1.png");
		tile->sprite.setTexture(*txr);
		tile->interaction = NONE;
		tile->collidable = true;
		tile->interactable = false;
		break;
	}
	case TileType::ENTRANCE_DOOR:
	{
		tile->ID = 8;
		txr->loadFromFile("dngn_closed_door");
		tile->sprite.setTexture(*txr);
		tile->interaction = NONE;
		tile->collidable = true;
		tile->interactable = true;
		break;
	}
	case TileType::EXIT_DOOR:
	{
		tile->ID = 9;
		txr->loadFromFile("Grafiki/dngn_altar.png");
		tile->sprite.setTexture(*txr);
		tile->interaction = TELEPORT;
		tile->collidable = true;
		tile->interactable = true;
		break;
	}
	case TileType::PAD_1:
	{
		tile->ID = 10;
		txr->loadFromFile("Grafiki/pad_1.png");
		tile->sprite.setTexture(*txr);
		tile->interaction = NONE;
		tile->collidable = true;
		tile->interactable = false;
		break;
	}
	case TileType::ALTAR_1:
	{
		tile->ID = 11;
		txr->loadFromFile("Grafiki/dngn_altar.png");
		tile->sprite.setTexture(*txr);
		tile->interaction = NONE;
		tile->collidable = true;
		tile->interactable = false;
		break;
	}
	case TileType::MARBLE_1:
	{
		tile->ID = 12;
		tile->texture->loadFromFile("Grafiki/marble_1.png");
		tile->sprite.setTexture(*texture);
		tile->interaction = NONE;
		tile->collidable = true;
		tile->interactable = false;
		break;
	}
	default:
		break;
	}

	return tile;
}

//---------------------------------------------------------------------------------------