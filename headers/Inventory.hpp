#pragma once
#include "Item.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include "GraphicsManager.hpp"
#include <SDL.h>
#include <SDL_image.h>

class Inventory
{
public:
    Inventory(GraphicsManager& window);
    //Add items to inventory. Return true if successful, false if failed (not enough inventory space)
    bool addItem(Item item, GraphicsManager& window);
    //Remove given amount of item. Return true if successful, false if failed.
    bool removeItem(Item item, GraphicsManager& window);
    //Draws inventory.
    void draw(GraphicsManager& window);
    //Checks if player has item and if amount of item is less than or equal to amount in inventory.
    bool hasItem(Item item);
    //Gets an item's texture. Arguments: int i = item id-100 (texture to get)
    SDL_Texture* getItemTexture(int i) {return item_textures[i];}
    //Get item from slot in inventory. 1 = first slot
    Item getItemFromSlot(int slot) {return items[slot-1];}
    //Checks if inventory is full
    bool isFull();
    //Saves inventory to file
    void save(const char* p_file);
    //Loads inventory from file
    void loadInv(const char* p_file, GraphicsManager& window);
private:
    Item items[10];
    //An array holding all item textures. Texture spot = item id-100
    SDL_Texture* item_textures[18];
    SDL_Texture* bar_tex;
};
