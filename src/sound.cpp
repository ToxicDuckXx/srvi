#include "Sounds.hpp"

int Sound::playSound(const char* path)
{
    bool i = PlaySoundA(path, NULL, SND_NODEFAULT);
    if (i)
    {
        return 0;
    }
    return 1;
}