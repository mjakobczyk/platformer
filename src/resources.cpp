#include "../include/basic.h"

//---------------------------------------------------------------------------------------

const std::string Resources::graphicsDirectory = "../resources/Grafiki/";

const std::string Resources::fontsDirectory = "../resources/Czcionki/";

//---------------------------------------------------------------------------------------

std::string Resources::getMenuBackgroundTexture()
{
    return Resources::graphicsDirectory + "backg1.jpg";
}

//---------------------------------------------------------------------------------------

std::string Resources::getMenuBackgroundFont()
{
    return Resources::fontsDirectory  + "BLOCKSS.otf";
}

//---------------------------------------------------------------------------------------

std::string Resources::getWarlockTexture()
{
    return Resources::graphicsDirectory  + "warlock_of.png";
}

//---------------------------------------------------------------------------------------

std::string Resources::getMageTexture()
{
    return Resources::graphicsDirectory  + "mage_of.png";
}

//---------------------------------------------------------------------------------------

std::string Resources::getPriestTexture()
{
    return Resources::graphicsDirectory  + "priest_of.png";
}

//---------------------------------------------------------------------------------------

std::string Resources::getFireballTexture()
{
    return Resources::graphicsDirectory  + "fireball.png";
}

//---------------------------------------------------------------------------------------

std::string Resources::getFrostboltTexture()
{
    return Resources::graphicsDirectory  + "fireball.png";
}

//---------------------------------------------------------------------------------------

std::string Resources::getShadowboltTexture()
{
    return Resources::graphicsDirectory  + "fireball.png";
}

//---------------------------------------------------------------------------------------