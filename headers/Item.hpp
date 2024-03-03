#pragma once

struct Item
{
    Item()
    :id(0),amount(0),name(nullptr)
    {}
    Item(int p_id, int p_amount, const char* p_name)
    :id(p_id),amount(p_amount),name(p_name)
    {}
    int id;
    int amount;
    const char* name;
};
