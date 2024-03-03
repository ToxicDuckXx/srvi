#include "DragonAttack.hpp"
#include <cmath>
#include "Math.hpp"
#include <iostream>

void DragonAttack::update(Monster& monster, Player& player, bool is_nextto_player, GraphicsManager& world)
{   
    Vector2f camera = player.getWorldCam();
    Vector2f pos2 = Vector2f(fireball_pos.x - camera.x, fireball_pos.y-camera.y);
    if (fireball_shown)
    {
        world.renderRelativeToCamera(camera, Vector2f(fireball_pos.x, fireball_pos.y), Vector2f(75, 75), fireball_tex);
        fireball_pos.x += fireball_dir.x * 6;
        fireball_pos.y += fireball_dir.y * 6;
        if (sqrt(((576-pos2.x)*(576-pos2.x))+((296-pos2.y)*(296-pos2.y))) <= 50)
        {
            player.onHit(25);
            player.applyEffect(effects::EFFECT_BURNING, 25);
            fireball_shown = false;
            fireball_cooldown = 180;
        }
        else if (sqrt(((monster.xy.x-fireball_pos.x)*(monster.xy.x-fireball_pos.x))+((monster.xy.y-fireball_pos.y)*(monster.xy.y-fireball_pos.y))) >= 576)
        {
            fireball_shown = false;
            fireball_cooldown = 180;
        }
    }

    
    if ((is_nextto_player)&&(regular_attack_cooldown <= 0))
    {
        //Regular Attack
        regular_attack_cooldown = 120;
        player.onHit(15);
    }

    //Fireball
    if ((sqrt(((608-((monster.xy.x-camera.x)+50))*(608-((monster.xy.x-camera.x)+50)))+((328-(monster.xy.y-camera.y+50))*(328-(monster.xy.y-camera.y+50)))) <= 400)&&(fireball_cooldown <= 0)&&(!(fireball_shown)))
    {
        fireball_cooldown = 300;
        fireball_shown = true;
        fireball_pos = Vector2f(monster.xy.x, monster.xy.y);
        Vector2f pos = Vector2f(monster.xy.x - camera.x, monster.xy.y - camera.y);
        float f_distance = sqrt(((576-pos.x)*(576-pos.x))+((296-pos.y)*(296-pos.y)));
        fireball_dir.x = (576-pos.x) / f_distance;
        fireball_dir.y = (296-pos.y) / f_distance;
    }
    regular_attack_cooldown -= 1;
    if (!(fireball_shown)) fireball_cooldown -= 1;
    
}