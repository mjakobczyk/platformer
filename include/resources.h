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

    static const std::string graphicsDirectory;
    static const std::string fontsDirectory;
};

#endif