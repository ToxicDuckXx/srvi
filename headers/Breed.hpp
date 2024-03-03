#pragma once
#include "MonsterAiComp.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"
#include "AttackAiComp.hpp"

struct Breed
{
    Breed()
    :health(0), ai(nullptr), speed(0), tex(nullptr), size(Vector2f()), attack(nullptr)
    {}
    Breed(int p_health, MonsterAiComp* p_ai, AttackAiComp* p_attack, int p_speed, SDL_Texture* p_tex, Vector2f p_size)
    :health(p_health), ai(p_ai), speed(p_speed), tex(p_tex), size(p_size), attack(p_attack)
    {}
    int health;
    MonsterAiComp* ai;
    AttackAiComp* attack;
    int speed;
    SDL_Texture* tex;
    Vector2f size;
};
