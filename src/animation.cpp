#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Animation::Animation()
{
	imageCount = sf::Vector2u(4, 4); // Przewa¿nie wszystkie animacjee bêd¹ tekstur¹ 4x4
	switchTime = 0.2f; // Przyk³adowy switchtime, mo¿na daæ wolniejszy
	totalTime = 0.0f; // Ca³kowity czas inicjalizujemy 0
	currentImage.x = 0; // Na pocz¹tku chcemy pierwszy obrazek
	forward = true;

	sf::Texture texture;
	texture.loadFromFile("Grafiki/warlock_of.png");

	uvRect.width = texture.getSize().x / float(imageCount.x);
	uvRect.height = texture.getSize().y / float(imageCount.y);
}

//---------------------------------------------------------------------------------------

Animation::Animation(sf::Texture * texture_)
{
	imageCount = sf::Vector2u(4, 4); // Przewa¿nie wszystkie animacjee bêd¹ tekstur¹ 4x4
	switchTime = 0.5f; // Przyk³adowy switchtime, mo¿na daæ wolniejszy
	totalTime = 0.0f; // Ca³kowity czas inicjalizujemy 0
	currentImage.x = 0; // Na pocz¹tku chcemy pierwszy obrazek
	forward = true;

	uvRect.width = (*texture_).getSize().x / float(imageCount.x);
	uvRect.height = (*texture_).getSize().y / float(imageCount.y);
}

//---------------------------------------------------------------------------------------

Animation::Animation(sf::Vector2u imageCount_, float switchTime_)
{
	imageCount = imageCount_;
	switchTime = switchTime_;
	totalTime = 0.0f;
	currentImage.x = 0;
	forward = true;

	sf::Texture texture;
	texture.loadFromFile("Grafiki/warlock_of.png");

	uvRect.width = texture.getSize().x / float(imageCount.x);
	uvRect.height = texture.getSize().y / float(imageCount.y);
}

//---------------------------------------------------------------------------------------

Animation::Animation(sf::Texture * texture_, sf::Vector2u imageCount_, float switchTime_)
{
	imageCount = imageCount_;
	switchTime = switchTime_;
	totalTime = 0.0f;
	currentImage.x = 0;
	forward = true;

	uvRect.width = texture_->getSize().x / float(imageCount.x);
	uvRect.height = texture_->getSize().y / float(imageCount.y);
}

//---------------------------------------------------------------------------------------

Animation::~Animation() 
{
	;
}

//---------------------------------------------------------------------------------------


void Animation::setSwitchTime(float switchTime_)
{
	this->switchTime = switchTime_;
}

//---------------------------------------------------------------------------------------

void Animation::setSize(sf::Texture texture_)
{
	uvRect.width = texture_.getSize().x / float(imageCount.x);
	uvRect.height = texture_.getSize().y / float(imageCount.y);
}

//---------------------------------------------------------------------------------------

void Animation::setImageCount(sf::Vector2u imageCount_)
{
	this->imageCount = imageCount_;
}

//---------------------------------------------------------------------------------------

bool Animation::isForward()
{
	return this->forward;
}

//---------------------------------------------------------------------------------------

void Animation::update(int row_, float deltaTime_, bool faceRight_)
{
	currentImage.y = row_;
	totalTime += deltaTime_;

	if (totalTime >= switchTime && imageCount.x > 1)
	{
		totalTime -= switchTime;

		if (forward)
		{
			if (currentImage.x + 1 >= imageCount.x)
			{
				currentImage.x = imageCount.x - 1;
				forward = false;
			}
			else
			{
				currentImage.x++;
			}
		}
		else
		{
			if (currentImage.x - 1 <= 0)
			{
				currentImage.x = 0;
				forward = true;
			}
			else
			{
				currentImage.x--;
			}
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

//---------------------------------------------------------------------------------------