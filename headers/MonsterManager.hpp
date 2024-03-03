#pragma once
#include "GraphicsManager.hpp"
#include "Player.hpp"
#include "World.hpp"
#include <vector>
#include "Camera.hpp"
#include "Monster.hpp"
#include "Breed.hpp"
#include "Math.hpp"

class MonsterManager
{
public:
    MonsterManager(GraphicsManager& window);
    void update(Camera& cam, World& world, GraphicsManager& window, Player& player);
    Monster* hitMonster(Camera& camera, int radius);
private:
    Breed breeds[5];   
    std::vector<Monster*> monsters;
    Vector2f getRandCords();
    int monster_spawn_time;
    bool entered_winter;
    int passive_spawn_time;
};