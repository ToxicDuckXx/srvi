#include "WolfAi.hpp"
#include <cmath>

bool WolfAi::update(World& world, GraphicsManager& window, Camera& camera, Monster& monster, SDL_Texture* tex)
{
    
    //Movement Code (Player cords = 576, 296)
    Vector2f pos = Vector2f(monster.xy.x-camera.getPos().x, monster.xy.y-camera.getPos().y);
    float distance = sqrt(((576-pos.x)*(576-pos.x))+((296-pos.y)*(296-pos.y)));
    float directionX = (576-pos.x) / distance;
    float directionY = (296-pos.y) / distance;
    float angle;
    bool can_see = true;
    if (distance >= 500) 
    {
        can_see = false;
        angle = 0;
    }
    else{
        angle = atan2(328-(pos.y+50), 608-(pos.x+50))*57.2957795147+270;
    }
    pos.x += directionX * monster.getSpeed();
    pos.y += directionY * monster.getSpeed();
    window.renderRelativeToCameraEx(camera, Vector2f(pos.x + camera.getPos().x, pos.y + camera.getPos().y), Vector2f(100,100), tex, angle);
    if (sqrt(((608-(pos.x+50))*(608-(pos.x+50)))+((328-(pos.y+50))*(328-(pos.y+50)))) <= 75)
    {
        return true;
    }
    if (world.resolveCollision(pos, 100, camera, Vector2f(directionX*monster.getSpeed(), directionY*monster.getSpeed()))||(!(can_see)))
    {
        return false;
    }
    monster.xy = Vector2f(pos.x + camera.getPos().x, pos.y + camera.getPos().y);
    return false;

}