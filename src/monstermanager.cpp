#include "MonsterManager.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "WolfAi.hpp"
#include "WolfAttack.hpp"
#include "Breed.hpp"
#include <cmath>
#include <iostream>
#include "SpiderAttack.hpp"
#include "NoAttakAiComp.hpp"
#include "DragonAttack.hpp"
#include "PassiveAi.hpp"

MonsterManager::MonsterManager(GraphicsManager& window)
:monster_spawn_time(0), entered_winter(false), passive_spawn_time(0)
{
    SDL_Texture* wolf_tex = window.loadTexture("res/wolf.png");
    SDL_Texture* spider_tex = window.loadTexture("res/spider.png");
    SDL_Texture* drag_tex = window.loadTexture("res/dragon.png");
    SDL_Texture* fireball_tex = window.loadTexture("res/fireball.png");
    SDL_Texture* sheep_tex = window.loadTexture("res/sheep.png");
    breeds[0] = Breed(50, new WolfAi(), new WolfAttack(), 1, wolf_tex, Vector2f(100,100));
    breeds[1] = Breed(50, new WolfAi(), new SpiderAttack(), 1, spider_tex, Vector2f(100,100));
    breeds[2] = Breed(75, new WolfAi(), new WolfAttack(), 2, wolf_tex, Vector2f(100,100));
    breeds[3] = Breed(1000, new WolfAi(), new DragonAttack(fireball_tex), 3, drag_tex, Vector2f(100, 100));
    breeds[4] = Breed(40, new PassiveAi(), new NoAttackAiComp(), 1, sheep_tex, Vector2f(100,100));
}
void MonsterManager::update(Camera& cam, World& world, GraphicsManager& window, Player& player)
{   
    //TODO FIX THIS ITS SUPER MESSY
    if ((!(entered_winter))&&(world.getCurrentMapId() == 2))
    {
        entered_winter = true;
        monsters.push_back(new Monster(breeds[3], Vector2f(100, 100), 2));
    }
    //TODO Clean up monster deletion code. Should be better way to implement.
    monster_spawn_time += 1;
    passive_spawn_time += 1;
    int element_to_erase = -1;
    for (int i = 0; i < monsters.size(); i++)
    {
        if ((fabs(monsters.at(i)->xy.x-576 - cam.getPos().x)>2500)||(fabs(monsters.at(i)->xy.y - 296 - cam.getPos().y)>2500))
        {
            if (!(monsters[i]->getId() == 2 || monsters[i]->getId() == 3))
            {
                element_to_erase = i;
            }
            
        }
        monsters.at(i)->update(window, cam, world, player);
        if (monsters.at(i)->getHealth() <= 0)
        {
            //dragon
            if (monsters.at(i)->getId() == 2)
            {
                player.addItemById(115, window);
            }
            else if (monsters.at(i)->getId() == 3)
            {
                player.addItemById(116, window);
            }
            element_to_erase = i;
        }
    }
    if (!(element_to_erase==-1)) {
        delete monsters.at(element_to_erase);
        monsters.erase(monsters.begin()+element_to_erase);
    }
    //SWITCH BACK TO 1800
    if ((monster_spawn_time >= 1000)&&(!(world.getIsDay()))&&(world.getCurrentMapId() == 1))
    {
        monster_spawn_time = 0;
        int monster_type = rand() % 2 + 1;
        Vector2f chords = getRandCords();
        if (monster_type == 1)
        {
            monsters.push_back(new Monster(breeds[0], Vector2f(chords.x+cam.getPos().x, chords.y + cam.getPos().y), 1));
        }
        else if (monster_type == 2)
        {
            monsters.push_back(new Monster(breeds[1], Vector2f(chords.x+cam.getPos().x, chords.y + cam.getPos().y), 1));
        }
        
        
    }
    if ((passive_spawn_time >= 3000)&&(world.getCurrentMapId() == 1)) {
        passive_spawn_time = 0;
        Vector2f chords = getRandCords();
        monsters.push_back(new Monster(breeds[4], Vector2f(chords.x+cam.getPos().x, chords.y + cam.getPos().y), 3));
    }
    else if ((world.getCurrentMapId() == 2)&&(monster_spawn_time >= 500))
    {
        monster_spawn_time = 0;
        Vector2f chords = getRandCords();
        monsters.push_back(new Monster(breeds[2], Vector2f(chords.x + cam.getPos().x, chords.y + cam.getPos().x), 1));
    }
}

Monster* MonsterManager::hitMonster(Camera& camera, int radius)
{
    //player pos=576,296
    for (Monster* m : monsters)
    {
        int d_x, d_y;
        d_x = (m->xy.x+50-camera.getPos().x)-608;
        d_y = (m->xy.y+50-camera.getPos().y)-328;
        float distance = sqrt((d_x*d_x)+(d_y*d_y));
        if (distance <= 100 + radius)
        {
            float angle_to_mouse, angle_to_object;
            int xMouse, yMouse;
            SDL_GetMouseState(&xMouse, &yMouse);
            angle_to_mouse = atan2(yMouse-328, xMouse-608)*57.2957795131;
            angle_to_object = atan2(m->xy.y-camera.getPos().y-328, m->xy.x-camera.getPos().x-608)*57.2957795131;
            if (fabs(angle_to_mouse-angle_to_object) < 90)
            {
                return m;
            }
        }
    }
    return NULL;
}   

Vector2f MonsterManager::getRandCords() 
{
    int quadrant = rand() % 4 + 1;
    Vector2f chords;
    if (quadrant == 1)
    {
        chords.x = (rand() % 1280 + 1)*-1;   
        chords.y = rand() % 720 + 1;
    }
    else if (quadrant == 2)
    {
        chords.x = rand() % 1280 + 1;
        chords.y = (rand() % 720 + 1)*-1;
    }
    else if (quadrant == 3)
    {
        chords.x = rand() % 2650 + 1280;
        chords.y = rand() % 720 + 1;
    }
    else
    {
        chords.x = rand() % 1280 + 1;
        chords.y = rand() & 1440 + 720;
    }
    return chords;
}