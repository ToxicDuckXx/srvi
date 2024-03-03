#pragma once
#include "Monster.hpp"
#include "Player.hpp"
#include "AttackAiComp.hpp"
#include "GraphicsManager.hpp"

class WolfAttack : public AttackAiComp
{
public:
    void update(Monster& monster, Player& player, bool is_nextto_player, GraphicsManager& world);
private:
    int cooldown = 0;
};
