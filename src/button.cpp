#include <SFML/Graphics.hpp>
#include "../include/button.h"
#include "../include/constants.h"

//---------------------------------------------------------------------------------------

Button::Button()
{
	this->text.setCharacterSize(65);
	this->text.setFillColor(sf::Color::Red);
	this->text.setString("DEFAULT");
	this->text.setPosition(sf::Vector2f((Constants::width() / 2 - this->text.getGlobalBounds().width), Constants::height() / 2));
}

//---------------------------------------------------------------------------------------

Button::Button(int charSize, const std::string & buttonName)
{
	this->text.setCharacterSize(charSize);
	this->text.setFillColor(sf::Color::Red);
	this->text.setString(buttonName);
	this->text.setPosition(sf::Vector2f((Constants::width() / 2 - this->text.getGlobalBounds().width), Constants::height() / 2));
}

//---------------------------------------------------------------------------------------

Button::~Button() {}

//---------------------------------------------------------------------------------------

sf::Text Button::getText()
{
	return this->text;
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

void Button::draw(sf::RenderWindow & whichWindow)
{
	whichWindow.draw(this->text);
}

//---------------------------------------------------------------------------------------
