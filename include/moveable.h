#ifndef MOVEABLE_H_
#define MOVEABLE_H_

// Klasa poruszaj¹cej siê jednostki
class Moveable : public Entity
{

public:
	Moveable();
	virtual ~Moveable();

	virtual void draw(sf::RenderWindow &) = 0;
	virtual bool collision(Entity *) = 0;
	virtual void update(float) = 0;
};

#endif