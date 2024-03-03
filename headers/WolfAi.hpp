#pragma once
#include "Math.hpp"
#include "MonsterAiComp.hpp"
#include "GraphicsManager.hpp"
#include "Camera.hpp"
#include "World.hpp"
#include "Monster.hpp"

class WolfAi : public MonsterAiComp
{
public:
    bool update(World& world, GraphicsManager& window, Camera& camera, Monster& monster, SDL_Texture* tex);
};