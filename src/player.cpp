#include "Player.hpp"
#include "WorldTile.hpp"
#include <iostream>
#include <cmath>
#include "MonsterManager.hpp"
#include "Monster.hpp"

Player::Player(SDL_Texture* p_tex, GraphicsManager& window)
:tex(p_tex), inventory(window), hit_cooldown(0), held_item(Item(100, 1, nullptr)), health(100), water_bar(100), time_till_waterbar(500), temp_bar(50), held_item_rotation(180)
{
    web_tex = window.loadTexture("res/spiderweb.png");
    bar_tex = window.loadTexture("res/bar_outline.png");
}

void Player::update(Vector2f vel, Camera& camera, GraphicsManager& window, World& world)
{

    vel.normalize();
    vel.x *= 4;
    vel.y *= 4;

    world_cam = camera.getPos();
    //Map stuff
    if ((camera.getPos().y < 896)&&(world.getCurrentMapId() == 1))
    {
        world.unloadMap();
        world.loadMap(2, window);
        camera.setPos(Vector2f(camera.getPos().x, 12800));

    }
    else if ((camera.getPos().y > 12800)&&(world.getCurrentMapId() == 2))
    {
        world.unloadMap();
        world.loadMap(1, window);
        camera.setPos(Vector2f(camera.getPos().x, 896));
    }

    //health bar
    window.renderBar(Vector2f(1070, 650), health*2, 217, 75, 28, bar_tex);
    window.renderBar(Vector2f(1070, 600), water_bar*2, 54, 120, 173, bar_tex);
    if (temp_bar <= 30)
    {
        window.renderBar(Vector2f(1070, 550), temp_bar*2, 55, 219, 219, bar_tex);
        //ADD DIMINISHING HEALTH
    }
    else if (temp_bar >= 75)
    {
        window.renderBar(Vector2f(1070, 550), temp_bar*2, 232, 92, 53, bar_tex);
    }
    else
    {
        window.renderBar(Vector2f(1070, 550), temp_bar*2, 178, 227, 79, bar_tex);
    }
    if (world.getCurrentMapId() == 2)
    {
        temp_bar -= .01;
    }
    

    time_till_waterbar -= 1;
    if (time_till_waterbar == 0)
    {
        time_till_waterbar = 240;
        water_bar -= 1;
    }
    if ((world.getTileIdAt(Vector2f(608, 328), camera) == 1)&&(water_bar < 100))
    {
        water_bar += 1;
    }

    drawHeldItem(window);
    hit_cooldown -= 1;
    inventory.draw(window);
    window.renderTwordsCurser(Vector2f(576, 296), Vector2f(64,64), tex, Vector2f(0,0));
    crafting.draw(window, inventory);

    if ((active_effect == effects::EFFECT_WEB_SLOW)&&(effect_duration > 0))
    {
        vel.x = vel.x/8;
        vel.y = vel.y/8;
        window.render(Vector2f(576, 296), Vector2f(128,128), web_tex);
    }
    if ((active_effect == effects::EFFECT_BURNING)&&(effect_duration > 0))
    {
        health -= 1;
    }
    
    if (world.resolveCollision(Vector2f(576, 296), 64, camera , vel))
    {
        camera.vel.x = 0;
        camera.vel.y = 0;
        return;
    }
    
    camera.vel.x = vel.x;
    camera.vel.y = vel.y;

    effect_duration -= 1;
    
}

void Player::onPress(World& world, Camera& camera, GraphicsManager& window, MonsterManager& mm)
{

    //held item rotation maths
    held_item_rotation = 0;
    

    Monster& m = *mm.hitMonster(camera, 20);
    if ((!(&m==NULL))&&(held_item.id == 105) && (hit_cooldown < 0))
    {
        m.setHealt(20);
        hit_cooldown = 20;
    }
    
    
    else if ((!(&m==NULL)) && (hit_cooldown < 0))
    {
        m.setHealt(5);
        hit_cooldown = 20;
    }

    //BERRY
    if (held_item.id == 104)
    {
        inventory.removeItem(Item(104, 1, nullptr), window);
        health += 50;
        if (health > 100) health = 100;
        if (!(inventory.hasItem(Item(held_item.id, 1, nullptr)))) held_item = Item(100, 1, nullptr);

    }

    Monster& m2 = *mm.hitMonster(camera, 300);
    if ((!(&m2==NULL))&&(held_item.id == 108) && (hit_cooldown < 0))
    {
        m2.setHealt(15);
        hit_cooldown = 40;
    }

    //Cup Stuff:
    if ((held_item.id == 111)&&(world.getTileIdAt(Vector2f(603,318), camera) == 1))
    {
        inventory.removeItem(Item(111, 1, nullptr), window);
        inventory.addItem(Item(112, 1, nullptr), window);
        held_item = Item(112, 1, "");
    }

    else if (held_item.id == 112)
    {
        water_bar = 100;
        inventory.removeItem(Item(112, 1, nullptr), window);
        inventory.addItem(Item(111, 1, nullptr), window);
        held_item = Item(111, 1, "");
    }

    //Flooring break detection

    else if (((held_item.id == 102)||(held_item.id == 106))&&(world.getTileIdAt(Vector2f(603,318), camera) == 9))
    {
        int tile_x, tile_y;
        SDL_GetMouseState(&tile_x, &tile_y);
        if (world.getTileIdAt(Vector2f(tile_x, tile_y), camera)==9)
        {
            tile_x = (tile_x + camera.getPos().x)/128;
            tile_y = (tile_y + camera.getPos().y)/128;
            world.setTile(Vector2f(tile_y, tile_x), 0);
        }

    }

    int i = world.hitObject(Vector2f(576, 296), camera);
    if (i == 2)
    {
        inventory.addItem(Item(101, 1, "WOOD"), window);
    }
    else if ((i == 3)&&((held_item.id == 102)||(held_item.id == 106)))
    {
        inventory.addItem(Item(103, 1, "ROCK"), window);
    }
    else if ((i == 11)&&(held_item.id == 106))
    {
        inventory.addItem(Item(114, 1, nullptr), window);
    }
    else if (i==6)
    {
        inventory.addItem(Item(104, 1, "BERRY"), window);
        world.setTile(Vector2f(world.last_hit_tile.x, world.last_hit_tile.y), 2);
    }
    else if ((i==5)&&(held_item.id == 106))
    {
        inventory.addItem(Item(107, 1, "GOLD"), window);
    }
    else if (((held_item.id == 102)||(held_item.id == 106))&&(i == 8))
    {
        int tile_x, tile_y;
        SDL_GetMouseState(&tile_x, &tile_y);
        tile_x = (tile_x + camera.getPos().x)/128;
        tile_y = (tile_y + camera.getPos().y)/128;
        world.setTile(Vector2f(tile_y, tile_x), 0);
    }

    
    if (held_item.id == 110)
    {
        inventory.removeItem(Item(held_item.id, 1, nullptr), window);
        int tile_x, tile_y;
        SDL_GetMouseState(&tile_x, &tile_y);
        tile_x = (tile_x + camera.getPos().x)/128;
        tile_y = (tile_y + camera.getPos().y)/128;
        world.setTile(Vector2f(tile_y, tile_x), 8);
        if (!(inventory.hasItem(Item(held_item.id, 1, nullptr)))) held_item = Item(100, 1, nullptr);
    }
    else if (held_item.id == 113)
    {
        inventory.removeItem(Item(held_item.id, 1, nullptr), window);
        int tile_x, tile_y;
        SDL_GetMouseState(&tile_x, &tile_y);
        tile_x = (tile_x + camera.getPos().x)/128;
        tile_y = (tile_y + camera.getPos().y)/128;
        world.setTile(Vector2f(tile_y, tile_x), 9);
        if (!(inventory.hasItem(Item(held_item.id, 1, nullptr)))) held_item = Item(100, 1, nullptr);
    }
    crafting.onPress(inventory, window);
    hit_cooldown -= 1;

}

void Player::drawHeldItem(GraphicsManager& window)
{//576, 296

    if (held_item.id == 100) return;

    if (held_item_rotation != 180)
    {
        held_item_rotation += 9;
    }

    SDL_Texture* tex = inventory.getItemTexture(held_item.id-100);
    int xMouse, yMouse;
    double angle;
    Vector2f center;
    SDL_GetMouseState(&xMouse, &yMouse);
    angle = atan2(yMouse-296, xMouse-576);
    center.x = cos(angle)*57.2957795147+598;
    center.y = sin(angle)*57.2957795147+318;
    window.renderEx(Vector2f(center.x-8, center.y-8), Vector2f(32,32), tex, (angle*57.2957795147+90)+(sin(held_item_rotation*.01745329)*57), Vector2f(center.x, center.y));
}                                                                                        

void Player::onPressKey(SDL_Keycode key, GraphicsManager& window)
{
    switch (key)
    {
    case SDLK_1:
        held_item = inventory.getItemFromSlot(1);
        break;
    case SDLK_2:
        held_item = inventory.getItemFromSlot(2);
        break;
    case SDLK_3:
        held_item = inventory.getItemFromSlot(3);
        break;
    case SDLK_4:
        held_item = inventory.getItemFromSlot(4);
        break;
    case SDLK_5:
        held_item = inventory.getItemFromSlot(5);
        break;
    case SDLK_6:
        held_item = inventory.getItemFromSlot(6);
        break;
    case SDLK_7:
        held_item = inventory.getItemFromSlot(7);
        break;
    case SDLK_8:
        held_item = inventory.getItemFromSlot(8);
        break;
    case SDLK_q:
        inventory.removeItem(Item(held_item.id, 1, nullptr), window);
        if (!(inventory.hasItem(Item(held_item.id, 1, nullptr))))
        {
            held_item = Item(100, 1, nullptr);
        }
        break;
    default:
        break;
    }
}

void Player::onHit(int dmg)
{
    health -= dmg;
    if (health < 0)
    {
        health = 0;
    }
}

void Player::applyEffect(effects::player_effect effect, int duration)
{
    effect_duration = duration;
    active_effect = effect;
}