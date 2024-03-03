#include "PassiveAi.hpp"
#include <cmath>

bool PassiveAi::update(World& world, GraphicsManager& window, Camera& camera, Monster& monster, SDL_Texture* tex)
{
    Vector2f pos = Vector2f(monster.xy.x-camera.getPos().x, monster.xy.y-camera.getPos().y);
    direction_timer -= 1;
    if (direction_timer <= 1000) 
    {
        vel.x = rand() % 10 - 6;
        vel.y = rand() % 10 - 6;
        direction_timer = 300;
    }
    float angle = atan2((pos.y+vel.y+50)-(pos.y+50), (pos.x+vel.x+50)-(pos.x+50));
    vel.normalize();
    pos.y += vel.y*monster.getSpeed();
    pos.x += vel.x*monster.getSpeed();
    window.renderRelativeToCameraEx(camera, Vector2f(pos.x + camera.getPos().x, pos.y + camera.getPos().y), Vector2f(100,100), tex, angle);
    monster.xy = Vector2f(pos.x + camera.getPos().x, pos.y + camera.getPos().y);
    return false;
}