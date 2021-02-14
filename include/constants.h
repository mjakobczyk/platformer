#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

// Constants hold useful information about game such as FPS, window height or width.
class Constants
{
public:
    static unsigned short FPS();
    static unsigned short height();
    static unsigned short width();
    static std::string text();
};

#endif