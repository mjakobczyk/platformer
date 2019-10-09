#ifndef BASIC_H_
#define BASIC_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "resources.h"
#include "game.h"
#include "entity.h"
#include "animation.h"
#include "moveable.h"
#include "spell.h"
#include "character.h"
#include "enemy.h"
#include "hero.h"
#include "game-over.h"
#include "stable.h"
#include "tile.h"
#include "button.h"
#include "interface.h"
#include "menu.h"
#include "level.h"
#include "engine.h"

#define FPS 60
#define HEIGHT 768
#define WIDTH 1280

class Game;
class Level;
class Button;
class Animation;
class Engine;
class Spell;

class Moveable;
class Character;
class Enemy;
class Hero;
class Warlock;
class Mage;
class Priest;

class Stable;
class Tile;

class Menu;
class MainMenu;
class Play;
class Options;
class Resources;

void test();
void test2();
void test3();
void test4();
std::string pobierzAktualnyCzas();
std::string convertSecondsToMinutes(float);
std::string convertIntToString(int);

#endif