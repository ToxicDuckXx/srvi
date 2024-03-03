#pragma once
#include "GraphicsManager.hpp"
#include <SDL.h>

class MiniMap
{
public:
    MiniMap(GraphicsManager& window);
    void update(Vector2f player_pos, GraphicsManager& window, int current_map);
private:
    SDL_Texture* map;
    SDL_Texture* marker;
};