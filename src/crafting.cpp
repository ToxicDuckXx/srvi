#include "Crafting.hpp"
#include "Item.hpp"
#include <iostream>

Crafting::Crafting()
{
    items = ReadItemFile::getItems();
}

void Crafting::draw(GraphicsManager& window, Inventory& inventory)
{
    
    for (int i=0; i<buttons.size();i++)
    {
        buttons[i].draw(window);
    }
}

void Crafting::onPress(Inventory& inventory, GraphicsManager& window)
{
    int length;
    buttons.clear();
    
    for (CraftableItem item : items)
    {
        if ((inventory.hasItem(item.mat1))&&(inventory.hasItem(item.mat2))&&(inventory.hasItem(item.mat3)))
        {
            length = buttons.size()+1;
            buttons.push_back(Button(Vector2f(10, (length-1)*100), Vector2f(100,100), inventory.getItemTexture(item.item.id-100), item.item.id));
        }
    }
    
    for (int i=0; i<buttons.size();i++)
    {
        if (buttons[i].onPress())
        {
            for (CraftableItem item : items)
            {
                if (buttons[i].id == item.item.id)
                {
                    if ((inventory.isFull())&&(!(inventory.hasItem(item.item)))) break;
                    if ((inventory.removeItem(item.mat1, window))&&(inventory.removeItem(item.mat2, window))&&(inventory.removeItem(item.mat3, window)))
                    {
                        item.item.amount = 1;
                        inventory.addItem(item.item, window);
                        buttons.clear();
                    }
                }
            }
            
            
        };
    }
}
