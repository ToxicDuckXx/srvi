#pragma once
#include "World.hpp"
#include "GraphicsManager.hpp"
#include "Camera.hpp"

class Monster;
class MonsterAiComp
{
public:
    virtual ~MonsterAiComp() {};
    virtual bool update(World& world, GraphicsManager& window, Camera& camera, Monster& monster, SDL_Texture* tex) = 0;
};