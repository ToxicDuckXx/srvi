#include "WolfAttack.hpp"

void WolfAttack::update(Monster& monster, Player& player, bool is_nextto_player, GraphicsManager& world)
{
    if (!(is_nextto_player)) return;
    if (cooldown <= 0)
    {
        player.onHit(5);
        cooldown = 61;
    }
    cooldown -= 1;
}