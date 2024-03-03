#pragma once
#include "GraphicsManager.hpp"
#include "Button.hpp"
#include "Inventory.hpp"
#include <vector>
#include "ReadItemFile.hpp"

class Crafting
{
public:
    Crafting();
    void draw(GraphicsManager& window, Inventory& inventory);
    //To be called when mouse pressed. Checks if buttons where pressed, and for updates in item amounts.
    void onPress(Inventory& inventory, GraphicsManager& window);
private:
    std::vector<Button> buttons;
    std::vector<CraftableItem> items;
};