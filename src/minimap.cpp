#include "MiniMap.hpp"

MiniMap::MiniMap(GraphicsManager& window)
{
    map = window.loadTexture("res/mini_map.png");
    marker = window.loadTexture("res/map_marker.png");
}

void MiniMap::update(Vector2f player_pos, GraphicsManager& window, int current_map)
{
    window.render(Vector2f(10, 610), Vector2f(100, 100), map);
    int posX, posY;
    if (current_map == 1)
    {
        
        posX = (player_pos.x/250)+10;
        posY = (player_pos.y/250)+660;
    }
    else if (current_map == 2)
    {
        posX = (player_pos.x/250)+10;
        posY = (player_pos.y/250)+605;
    }
    window.render(Vector2f(posX, posY), Vector2f(3,3), marker);

}