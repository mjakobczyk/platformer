#include "basic.h"

//---------------------------------------------------------------------------------------

Hero::Hero(heroSpec heroSpec_) :
	Character()
{
	this->spec = heroSpec_;
	this->lastCast.restart().asSeconds();
	this->spellCast = false;
}

//---------------------------------------------------------------------------------------

Hero::Hero(heroSpec heroSpec_, sf::Texture * texture, sf::Vector2u imageCount, float switchTime) :
	Character(texture, imageCount, switchTime) 
{
	this->spec = heroSpec_;
}

//---------------------------------------------------------------------------------------

Hero::~Hero()
{
	;
}

//---------------------------------------------------------------------------------------

Hero * Hero::getHero() 
{ 
	return this;
}

//---------------------------------------------------------------------------------------

void Hero::setSpec(heroSpec spec_)
{
	this->spec = spec_;
}

//---------------------------------------------------------------------------------------

bool Hero::isSpecSet()
{
	if (this->spec != unknown)
		return true;

	return false;
}

//---------------------------------------------------------------------------------------

bool Hero::isSpellCast()
{
	return this->spellCast;
}

//---------------------------------------------------------------------------------------

float Hero::getLastCast()
{
	return this->lastCast.getElapsedTime().asSeconds();
}

//---------------------------------------------------------------------------------------

void Hero::update(float diff)
{
	if (isSpellCast())
	{
		if (lastCast.getElapsedTime().asSeconds() > SPELL_COOLDOWN)
		{
			lastCast.restart().asSeconds();
			spellCast = false;
		}
	}

	this->Character::update(diff);
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

Warlock::Warlock() : Hero(heroSpec::warlock)
{
	spellPower = 50;

	sf::Texture * txr = new sf::Texture;
	if (!(*txr).loadFromFile("Grafiki/warlock_of.png"))
	{
		std::cout << "Blad tekstury! Warlock konstruktor" << std::endl;
		return;
	}
	this->setTexture(txr);
	this->sprite.setTextureRect(sf::IntRect(0, 96, 32, 48));
};

//---------------------------------------------------------------------------------------

Warlock::Warlock(sf::Texture * texture, sf::Vector2u imageCount, float switchTime) :
	Hero(heroSpec::warlock, texture, imageCount, switchTime)
{
	spellPower = 50;
};

//---------------------------------------------------------------------------------------

bool Warlock::castSpell()
{
	if (!spellCast)
	{
		spellCast = true;
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------------------------------------

Spell * Warlock::getSpell()
{
	std::cout << "Warlock is casting spell!" << std::endl;
	Fireball * fireball = new Fireball;
	return fireball;
}

//---------------------------------------------------------------------------------------

void Warlock::manaRefill()
{
	return;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

Mage::Mage() : Hero(heroSpec::mage)
{
	spellPower = 50;

	sf::Texture * txr = new sf::Texture;
	if (!(*txr).loadFromFile("Grafiki/mage_of.png"))
	{
		std::cout << "Blad tekstury! Mage konstruktor" << std::endl;
		return;
	}
	this->setTexture(txr);
	this->sprite.setTextureRect(sf::IntRect(0, 96, 32, 48));
};

//---------------------------------------------------------------------------------------

Mage::Mage(sf::Texture * texture, sf::Vector2u imageCount, float switchTime) :
	Hero(heroSpec::mage, texture, imageCount, switchTime)
{
	spellPower = 50;
};

//---------------------------------------------------------------------------------------

bool Mage::castSpell()
{
	if (!spellCast)
	{
		spellCast = true;
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------------------------------------

Spell * Mage::getSpell()
{
	std::cout << "Mage is casting spell!" << std::endl;
	Fireball * fireball = new Fireball;
	return fireball;
}

//---------------------------------------------------------------------------------------

void Mage::manaRefill()
{
	return;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

Priest::Priest() : Hero(heroSpec::priest)
{
	spellPower = 50;

	sf::Texture * txr = new sf::Texture;
	if (!(*txr).loadFromFile("Grafiki/priest_of.png"))
	{
		std::cout << "Blad tekstury! Priest konstruktor" << std::endl;
		return;
	}
	this->setTexture(txr);
	this->sprite.setTextureRect(sf::IntRect(0, 96, 32, 48));
};

//---------------------------------------------------------------------------------------

Priest::Priest(sf::Texture * texture, sf::Vector2u imageCount, float switchTime) :
	Hero(heroSpec::priest, texture, imageCount, switchTime)
{
	spellPower = 50;
};

//---------------------------------------------------------------------------------------

bool Priest::castSpell()
{
	if (!spellCast)
	{
		spellCast = true;
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------------------------------------------------------------------

Spell * Priest::getSpell()
{
	std::cout << "Priest is casting spell!" << std::endl;
	Fireball * fireball = new Fireball;
	return fireball;
}

//---------------------------------------------------------------------------------------

void Priest::manaRefill()
{
	return;
}

//---------------------------------------------------------------------------------------