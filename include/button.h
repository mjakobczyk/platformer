#ifndef BUTTON_H_
#define BUTTON_H_

// Button presents text and can interact with user 
class Button
{
public:
	void draw(sf::RenderWindow &);

	sf::Text getText();

	void setColor(const sf::Color);
	void setFont(const sf::Font &);
	void setName(const std::string &);
	void setPos(const sf::Vector2f &);
	void setSize(const int);

	Button();
	Button(int, const std::string &);
	~Button();

protected:
	sf::Text text;
};

#endif