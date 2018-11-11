#ifndef BUTTON_H_
#define BUTTON_H_

// Klasa przycisku, który mo¿e dzia³aæ jako w pe³ni funkcjonalny przycisk lub tylko napis
class Button
{
	sf::Text text; // Biblioteczna zmienna pozwalaj¹ca na modyfikacjê wyœwietlanego tekstu

public:
	Button();
	Button(int, const std::string &);
	~Button();

	sf::Text getText() { return text; } // Metoda pobieraj¹ca aktualny tekst przycisku

	void setPos(const sf::Vector2f &); // Metoda ustawiaj¹ca pozycjê przycisku na ekranie
	void setColor(sf::Color); // Metoda ustawiaj¹ca kolor tekstu w przycisku
	void setName(const std::string &); // Metoda ustawiaj¹ca nazwê przycisku
	void setFont(const sf::Font &); // Metoda ustawiaj¹ca czcionkê tekstowi przycisku
	void setSize(const int); // Metoda ustawiaj¹ca wielkoœæ tekstu przycisku
	void handleEvents(sf::Vector2f &); // Metoda okreœlaj¹ca jak przycisk ma siê zachowywaæ w interakcji
	void draw(sf::RenderWindow &); // Metoda wyœwietlaj¹ca przycisk
};

#endif