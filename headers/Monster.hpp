#pragma once
#include "Math.hpp"
#include "MonsterAiComp.hpp"
#include "GraphicsManager.hpp"
#include "Camera.hpp"
#include "World.hpp"
#include "AttackAiComp.hpp"
#include "Breed.hpp"
#include "Player.hpp"

class Monster
{
public:
    Monster(Breed& breed, Vector2f p_pos, int p_id)
    :ai(breed.ai), texture(breed.tex), health(breed.health), speed(breed.speed), attack(breed.attack), id(p_id)
    {xy = p_pos;}
    void update(GraphicsManager& window, Camera cam, World& world, Player& player)
    {
        bool a;
        a = ai->update(world, window, cam, *this, texture);
        attack->update(*this, player, a, window);
    }
    int getHealth() {return health;}
    int getSpeed() {return speed;}
    void setHealt(int dmg) {health-=dmg;} 
    int getId() {return id;}
    Vector2f xy;
    int velocity;
private:
    int id;
    int health;
    int speed;
    MonsterAiComp* ai;
    AttackAiComp* attack;
    SDL_Texture* texture;
};