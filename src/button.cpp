#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Button::Button()
{
	text.setCharacterSize(65);
	text.setFillColor(sf::Color::Red);
	text.setString("DEFAULT");
	text.setPosition(sf::Vector2f((WIDTH / 2 - text.getGlobalBounds().width), HEIGHT / 2));
}

//---------------------------------------------------------------------------------------

Button::Button(int charSize, const std::string & buttonName)
{
	text.setCharacterSize(charSize);
	text.setFillColor(sf::Color::Red);
	text.setString(buttonName);
	text.setPosition(sf::Vector2f((WIDTH / 2 - text.getGlobalBounds().width), HEIGHT / 2));
}

//---------------------------------------------------------------------------------------

Button::~Button()
{
	;
}

//---------------------------------------------------------------------------------------

void Button::setPos(const sf::Vector2f & position)
{
	this->text.setPosition(position);
}

//---------------------------------------------------------------------------------------

void Button::setColor(sf::Color newColor)
{
	this->text.setFillColor(newColor);
}

//---------------------------------------------------------------------------------------

void Button::setName(const std::string & newName)
{
	this->text.setString(newName);
}

//---------------------------------------------------------------------------------------

void Button::setFont(const sf::Font & font)
{
	this->text.setFont(font);
}

//---------------------------------------------------------------------------------------

void Button::setSize(const int size)
{
	text.setCharacterSize(size);
}

//---------------------------------------------------------------------------------------

void Button::handleEvents(sf::Vector2f & mouse)
{
	if (this->text.getGlobalBounds().contains(mouse))
		this->text.setFillColor(sf::Color::Cyan);
	else
		this->text.setFillColor(sf::Color::White);
}

//---------------------------------------------------------------------------------------

void Button::draw(sf::RenderWindow & whichWindow)
{
	whichWindow.draw(this->text);
}
//---------------------------------------------------------------------------------------
