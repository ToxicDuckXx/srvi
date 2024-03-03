#pragma once
#include "AttackAiComp.hpp"

class NoAttackAiComp : public AttackAiComp
{
public:
    void update(Monster& monster, Player& player, bool is_nextto_player, GraphicsManager& world)
    {}
};