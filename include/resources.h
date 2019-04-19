#ifndef RESOURCES_H_
#define RESOURCES_H_
#include <string>

class Resources
{
public:
    static std::string getMenuBackgroundTexture();
    static std::string getMenuBackgroundFont();
    static std::string getWarlockTexture();
    static std::string getMageTexture();
    static std::string getPriestTexture();
    static std::string getFireballTexture();
    static std::string getFrostboltTexture();
    static std::string getShadowboltTexture();
    static std::string getZombieTexture();
    static std::string getVillainTexture();
    static std::string getGameoverTexture();
    static std::string getHeartTexture();
    static std::string getClockTexture();
    static std::string getCoinTexture();
    static std::string getCoinPileTexture();
    static std::string getBackground4Texture();
    static std::string getBackground5Texture();
    static std::string getBrick1Texture();
    static std::string getBrick2Texture();
    static std::string getStone1Texture();
    static std::string getLava11Texture();
    static std::string getLava2Texture();
    static std::string getWater1Texture();
    static std::string getClosedDoorsTexture();
    static std::string getAltarTexture();
    static std::string getPad1Texture();
    static std::string getMarble1Texture();
    static std::string getExitDoorsTexture();

    static const std::string graphicsDirectory;
    static const std::string fontsDirectory;
};

#endif