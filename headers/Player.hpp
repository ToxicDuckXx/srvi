#pragma once
#include "Math.hpp"
#include "Camera.hpp"
#include "GraphicsManager.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "World.hpp"
#include "Inventory.hpp"
#include "Crafting.hpp"
#include "Item.hpp"

namespace effects
{
    enum player_effect
    {
        EFFECT_WEB_SLOW,
        EFFECT_SLOW,
        EFFECT_FIRE,
        EFFECT_BURNING
    };
}

class MonsterManager;
class Player
{
public:
    Player(SDL_Texture* p_tex, GraphicsManager& window);
    void update(Vector2f vel, Camera& camera, GraphicsManager& window, World& world);
    void onPress(World& world, Camera& camera, GraphicsManager& window, MonsterManager& mm);
    void onPressKey(SDL_Keycode key, GraphicsManager& window);
    void onHit(int dmg);
    void applyEffect(effects::player_effect effect, int duration);
    void save() {inventory.save("res/saves/hi_inv.txt");}
    void addItemById(int id, GraphicsManager& window) {inventory.addItem(Item(id, 1, ""), window);}
    Vector2f getWorldCam() {return world_cam;}
private:
    SDL_Texture* tex;
    SDL_Texture* bar_tex;
    bool isFacingTwoards(Vector2f point);
    void drawHeldItem(GraphicsManager& window);
    Inventory inventory;
    Crafting crafting;
    int hit_cooldown;
    Item held_item;
    int animate_held_angle_offset;
    int health;
    int water_bar;
    float temp_bar;
    int time_till_waterbar;
    int held_item_rotation;
    
    int effect_duration = 0;
    effects::player_effect active_effect;
    SDL_Texture* web_tex;
    Vector2f world_cam;
        
    
};