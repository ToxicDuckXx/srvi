#include "SpiderAttack.hpp"
#include "Math.hpp"
#include <iostream>

void SpiderAttack::update(Monster& monster, Player& player, bool is_nextto_player, GraphicsManager& world)
{
    if (!(is_nextto_player)) return;
    if (cooldown <= 0)
    {
        player.onHit(5);
        cooldown = 61;
    }
    

    if (web_attack_cooldown <= 0)
    {
        web_attack_cooldown = 300;
        player.applyEffect(effects::EFFECT_WEB_SLOW, 240);
    }

    web_attack_cooldown -= 1;
    cooldown -= 1;

}