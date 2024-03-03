#include "ReadItemFile.hpp"
#include <fstream>
#include <string>

std::vector<CraftableItem> ReadItemFile::getItems()
{
    std::vector<CraftableItem> to_return;
    std::ifstream infile("res/items/items.item");
    std::string line;
    while (std::getline(infile, line))
    {
        if (line.front() == '/') continue;
        int first_del;
        first_del = 0;
        size_t pos = 0;
        Item item;
        Item mat1;
        Item mat2;
        Item mat3;
        for (int i = 1; i < 8; i++)
        {
            pos = line.find(",");
            switch (i)
            {
            case 1:
                item.name = line.substr(0, pos).c_str();
                break;
            case 2:
                item.id = std::stoi(line.substr(0, pos));
                break;
            case 3:
                mat1.id = std::stoi(line.substr(0, pos));
                break;
            case 4:
                mat1.amount = std::stoi(line.substr(0, pos));
                break;
            case 5:
                mat2.id = std::stoi(line.substr(0, pos));
                break;
            case 6:
                mat2.amount = std::stoi(line.substr(0, pos));
                break;
            case 7:
                mat3.id = std::stoi(line.substr(0, pos));
            default:
                mat3.amount = std::stoi(line.substr(0, pos));
                break;
            }
            line.erase(0, pos + 1);
        }
        to_return.push_back(CraftableItem(item, mat1, mat2, mat3));
    }
    infile.close();
    return to_return;
    
}