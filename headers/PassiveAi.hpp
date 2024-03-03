#pragma once
#include "MonsterAiComp.hpp"
#include "GraphicsManager.hpp"
#include "Camera.hpp"
#include "World.hpp"
#include "Monster.hpp"
#include "Math.hpp"

class PassiveAi : public MonsterAiComp
{
public:
    PassiveAi()
    :direction_timer(0), vel(Vector2f(0,0))
    {}
    bool update(World& world, GraphicsManager& window, Camera& camera, Monster& monster, SDL_Texture* tex);
private:
    int direction_timer;
    Vector2f vel;
};