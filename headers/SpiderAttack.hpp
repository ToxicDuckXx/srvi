#pragma once
#include "Monster.hpp"
#include "Player.hpp"
#include "AttackAiComp.hpp"
#include "WorldTile.hpp"
#include "GraphicsManager.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Monster.hpp"
#include <SDL.h>

class SpiderAttack : public AttackAiComp
{
public:
    void update(Monster& monster, Player& player, bool is_nextto_player, GraphicsManager& world);
private:
    int web_attack_cooldown = 0;
    int web_cool = 0;
    int cooldown = 0;
};