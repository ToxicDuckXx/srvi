#pragma once

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <dirent.h>
#endif
 
namespace Sound
{
    int playSound(const char* path);
}