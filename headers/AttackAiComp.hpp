#pragma once
#include "Player.hpp"

class Monster;
class AttackAiComp
{
public:
    virtual ~AttackAiComp() {};
    virtual void update(Monster& monster, Player& player, bool is_nextto_player, GraphicsManager& world) = 0;
};