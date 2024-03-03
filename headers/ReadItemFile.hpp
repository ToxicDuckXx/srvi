#pragma once
#include "Item.hpp"
#include <vector>

struct CraftableItem
{
    CraftableItem()
    :item(), mat1(), mat2(), mat3()
    {}
    CraftableItem(Item p_item, Item p_mat1, Item p_mat2, Item p_mat3)
    :item(p_item), mat1(p_mat1), mat2(p_mat2), mat3(p_mat3)
    {}
    Item item;
    Item mat1;
    Item mat2;
    Item mat3;
};


namespace ReadItemFile
{
    std::vector<CraftableItem> getItems();
}