#include "../include/basic.h"

//---------------------------------------------------------------------------------------

Animation::Animation()
{
	this->imageCount = sf::Vector2u(4, 4);
	this->switchTime = 0.2f;
	this->totalTime = 0.0f;
	this->currentImage.x = 0;
	this->forward = true;

	sf::Texture texture;
	texture.loadFromFile(Resources::getWarlockTexture());

	this->uvRect.width = texture.getSize().x / float(imageCount.x);
	this->uvRect.height = texture.getSize().y / float(imageCount.y);
}

//---------------------------------------------------------------------------------------

Animation::Animation(sf::Texture * texture_)
{
	this->imageCount = sf::Vector2u(4, 4);
	this->switchTime = 0.5f;
	this->totalTime = 0.0f;
	this->currentImage.x = 0;
	this->forward = true;

	this->uvRect.width = (*texture_).getSize().x / float(imageCount.x);
	this->uvRect.height = (*texture_).getSize().y / float(imageCount.y);
}

//---------------------------------------------------------------------------------------

Animation::Animation(sf::Vector2u imageCount_, float switchTime_)
{
	this->imageCount = imageCount_;
	this->switchTime = switchTime_;
	this->totalTime = 0.0f;
	this->currentImage.x = 0;
	this->forward = true;

	sf::Texture texture;
	texture.loadFromFile(Resources::getWarlockTexture());

	this->uvRect.width = texture.getSize().x / float(imageCount.x);
	this->uvRect.height = texture.getSize().y / float(imageCount.y);
}

//---------------------------------------------------------------------------------------

Animation::Animation(sf::Texture * texture_, sf::Vector2u imageCount_, float switchTime_)
{
	this->imageCount = imageCount_;
	this->switchTime = switchTime_;
	this->totalTime = 0.0f;
	this->currentImage.x = 0;
	this->forward = true;

	this->uvRect.width = texture_->getSize().x / float(imageCount.x);
	this->uvRect.height = texture_->getSize().y / float(imageCount.y);
}

//---------------------------------------------------------------------------------------

Animation::~Animation() {}

//---------------------------------------------------------------------------------------

sf::IntRect Animation::getIntRect()
{
	return this->uvRect;
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