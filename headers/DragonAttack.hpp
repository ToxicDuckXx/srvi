#pragma once
#include "Monster.hpp"
#include "Player.hpp"
#include "AttackAiComp.hpp"
#include "WorldTile.hpp"
#include "GraphicsManager.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Math.hpp"
#include "Monster.hpp"
#include <SDL.h>

class DragonAttack : public AttackAiComp
{
public:
    DragonAttack(SDL_Texture* p_fire_ball_text)
    :fireball_tex(p_fire_ball_text)
    {}
    void update(Monster& monster, Player& player, bool is_nextto_player, GraphicsManager& world);
private:
    int cooldown = 0;
    bool fireball_shown = false;
    Vector2f fireball_pos;
    int regular_attack_cooldown = 0;
    int fireball_cooldown = 0;
    SDL_Texture* fireball_tex;
    Vector2f fireball_dir;
};