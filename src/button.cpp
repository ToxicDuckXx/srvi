#include "Button.hpp"

Button::Button(Vector2f p_pos, Vector2f p_size, SDL_Texture* p_tex, int p_id)
:pos(p_pos), size(p_size), texture(p_tex), id(p_id)
{

}

void Button::draw(GraphicsManager& window)
{
    window.render(pos, size, texture);
}

bool Button::onPress()
{
    int xMouse;
    int yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);
    if (xMouse >= pos.x && xMouse <= (pos.x + size.x) && yMouse >= pos.y && yMouse <= (pos.y + size.y))
    {
        return true;
    }
    return false;
}