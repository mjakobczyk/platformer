#ifndef CHARACTER_H_
#define CHARACTER_H_

enum Direction { UNKNOWN = 0, LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };

#define MIN_HEALTH 1
#define MAX_HEALTH 10

// Character is a movable object that can perform actions.
class Character : public Moveable
{
public:
	virtual void draw(sf::RenderWindow &);
	virtual bool collision(Entity *);
	virtual void update(float);
	
	int getHealth();
	Direction getLastDirection();
	sf::Vector2f getLastMovement();
	bool isFacingRight();
	bool isSpellPending();
	void move(sf::Vector2f);
	void slow(float);
	void hurt(float);

	void setX(float);
	void setY(float);
	void setName(const std::string &); 
	void setHealth(int);
	void setMana(int);
	void setDirection(bool);
	void setCollisionState(bool);

	Character();
	Character(sf::Texture*);
	Character(sf::Vector2u, float);
	Character(sf::Texture*, sf::Vector2u, float);
	virtual ~Character();

	bool canMoveRight, canMoveLeft, canJump, canFall;

protected:
	std::string name;
	int health, mana;
	
	sf::Vector2f movement;
	sf::Vector2f lastMovement;

	Animation animation;
	Direction lastDirection;

	unsigned int row;
	float tempDelta;
	float moveSpeed;
	float jumpSpeed;
	float gravity;
	float offset; 
	float groundHeight;
	bool faceRight, isJumping, isFalling, isColliding; 
	bool debuffActive; 
	bool pendingSpell;
};

#endif