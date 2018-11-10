#ifndef ANIMATION_H_
#define ANIMATION_H_

// Klasa animacji, wspomaga aktualizacje sprite'a w czasie dla obiektu
class Animation
{
protected:
	sf::Vector2u imageCount; // Okreœla rozmiar podawanej tekstury
	sf::Vector2u currentImage; // Okreœla aktualnie za³adowan¹ czêœæ tekstury
	sf::IntRect uvRect; // Czêœæ tekstury, któr¹ aktualnie potrzebujemy

	float totalTime; // Ca³kowity czas zmiany tekstury, nie mo¿e przekraczaæ switch time'u
	float switchTime; // Okreœla czêstoœæ zmian tekstury postaci
	bool forward; // Okreœla czy animacja pobiera kolejne czêœci tekstury w praw¹ stronê


public:
	Animation();
	Animation(sf::Texture*);
	Animation(sf::Vector2u, float);
	Animation(sf::Texture*, sf::Vector2u, float);
	~Animation();

	void setSwitchTime(float); // Ustawia czêstoœæ aktualizacji animacji
	void setSize(sf::Texture); // Ustawia rozmiar animacji na podstawie tekstury
	void setImageCount(sf::Vector2u); // Okreœla iloœæ podawanych klatek
	bool isForward(); // Sprawdza czy animacja pobiera klatki do przodu

	void update(int, float, bool); // Metoda aktualizuj¹ca animacjê
	sf::IntRect getIntRect() { return this->uvRect; } // Metoda zwracaj¹ca aktualn¹ czêœæ tekstury
};

#endif