#pragma once
#include "Math.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "GraphicsManager.hpp"

class Button
{
public:
    Button(Vector2f p_pos, Vector2f p_size, SDL_Texture* p_tex, int p_id);
    void draw(GraphicsManager& window);
    bool onPress();
    int id;
private:
    SDL_Texture* texture;
    Vector2f pos;
    Vector2f size;
};