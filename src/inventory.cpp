#include "Inventory.hpp"
#include "Math.hpp"
#include <iostream>
#include <string>
#include <fstream>

Inventory::Inventory(GraphicsManager& window)
{
    loadInv("res/saves/hi_inv.txt", window);
    // for (int i=0;i<8;i++)
    // {
    //     items[i] = Item(100, 0, "AIR");
    // }
    bar_tex = window.loadTexture("res/inventory_bar.png");
    item_textures[1] = window.loadTexture("res/wood.png");
    item_textures[2] = window.loadTexture("res/pickaxe.png");
    item_textures[3] = window.loadTexture("res/rock.png");
    item_textures[4] = window.loadTexture("res/cherry.png");
    item_textures[5] = window.loadTexture("res/stone_sword.png");
    item_textures[6] = window.loadTexture("res/stone_pickaxe.png");
    item_textures[7] = window.loadTexture("res/gold.png");
    item_textures[8] = window.loadTexture("res/staff.png");
    item_textures[10] = window.loadTexture("res/stone_wall.png");
    item_textures[11] = window.loadTexture("res/cup_empty.png");
    item_textures[12] = window.loadTexture("res/cup_full.png");
    item_textures[13] = window.loadTexture("res/floor.png");
    item_textures[14] = window.loadTexture("res/amethyst.png");
    item_textures[15] = window.loadTexture("res/key.png");
    item_textures[16] = window.loadTexture("res/wool.png");
    item_textures[17] = window.loadTexture("res/sweater.png");
}

bool Inventory::addItem(Item item, GraphicsManager& window)
{
    for (int i=0;i<8;i++)
    {
        if (items[i].id == item.id)
        {
            items[i].amount += item.amount;
            return true;
        }
    }
    for (int i=0;i<8;i++)
    {
        if (items[i].id == 100)
        {
            items[i] = item;
            return true;
        }
    }
    return false;
}

bool Inventory::removeItem(Item item, GraphicsManager& window)
{
    if (item.id == 109) return true;
    for (int i=0;i<8;i++)
    {
        if ((items[i].id == item.id)&&(items[i].amount >= item.amount))
        {
            items[i].amount -= item.amount;
            if (items[i].amount == 0)
            {
                items[i] = Item(100,0,"AIR");
            }
            return true;
        }
    }
    return false;
}

void Inventory::draw(GraphicsManager& window)
{
    window.render(Vector2f(340, 600), Vector2f(600, 100), bar_tex);
    for (int i=0;i<8;i++)
    {
        if (!(items[i].id == 100))
        {
            
            window.render(Vector2f(i*75+340, 610), Vector2f(70,70), item_textures[items[i].id-100]);
            window.renderBitmapNumber(Vector2f(i*75+395, 670), items[i].amount, 13);
        }
    }

}

bool Inventory::hasItem(Item item)
{
    if (item.id == 109)
    {
        return true;
    }
    for (int i=0;i<8;i++)
    {
        if ((items[i].id == item.id) && (items[i].amount >= item.amount))
        {
            return true;
        }
    }
    return false;
}

bool Inventory::isFull()
{
    for (int i=0;i<8;i++)
    {
        if (items[i].id == 100)
        {
            return false;
        }
    }
    return true;
}

void Inventory::save(const char* p_file)
{
    std::ofstream file;
    file.open(p_file);
    for (int i = 0; i < 8; i++)
    {
        std::string c;
        c = std::to_string(items[i].id) + "," + std::to_string(items[i].amount) + ",";
        file.write(c.c_str(), c.size());
    }
    file.close();
}

void Inventory::loadInv(const char* p_file, GraphicsManager& window)
{
    std::ifstream Invfile;
    Invfile.open(p_file);
    std::string line;
    std::getline(Invfile, line);
    size_t pos;
    for (int i = 0; i < 8; i++)
    {
        pos = line.find(",");
        items[i].id = std::stoi(line.substr(0,pos));
        line.erase(0, pos+1);
        pos = line.find(",");
        items[i].amount = std::stoi(line.substr(0, pos));
        line.erase(0, pos+1);
    }
    Invfile.close();
}
