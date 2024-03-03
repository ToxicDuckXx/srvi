#include "World.hpp"
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include "WolfAi.hpp"
#include "WolfAttack.hpp"

World::World()
:day_night(0), is_day(true), loaded_map(false), current_map(1)
{

}

void World::loadMap(int num, GraphicsManager& window)
{
    std::cout << "LOADING NEW MAP: loadMap() called." << std::endl;
    current_map = num;
    textures[0] = window.loadTexture("res/ground.png");
    textures[1] = window.loadTexture("res/water.png");
    textures[2] = window.loadTexture("res/bush.png");
    textures[3] = window.loadTexture("res/rock.png");
    textures[4] = window.loadTexture("res/obswater.png");
    textures[5] = window.loadTexture("res/gold.png");
    textures[6] = window.loadTexture("res/berry_bush.png");
    textures[7] = window.loadTexture("res/spiderweb.png");
    textures[8] = window.loadTexture("res/stone_wall.png");
    textures[9] = window.loadTexture("res/floor.png");
    textures[10] = window.loadTexture("res/snow.png");
    textures[11] = window.loadTexture("res/amethyst.png");
    
    //is solid, is circular, is water, texture
    tiles[0] = WorldTile(false, false, false, textures[0],0);
    tiles[1] = WorldTile(false, false, true, textures[1],1);
    tiles[2] = WorldTile(true, true, false, textures[2],2);
    tiles[3] = WorldTile(true, true, false, textures[3],3);
    //REMEBER TO SWITCH OBSWATER BACK TO SOLID!!!
    tiles[4] = WorldTile(false, false, false, textures[4],4);
    tiles[5] = WorldTile(true, true, false, textures[5],5);
    tiles[6] = WorldTile(true, true, false, textures[6],6);
    tiles[7] = WorldTile(true, false, false, textures[7], 7);
    tiles[8] = WorldTile(true, false, false, textures[8], 8);
    tiles[9] = WorldTile(false, false, false, textures[9], 9);
    tiles[10] = WorldTile(false, false, false, textures[10], 10);
    tiles[11] = WorldTile(true, true, false, textures[11], 11);
    tiles[12] = WorldTile(true, false, false, textures[8], 12);
    loaded_map = true;

    char tile;
    std::fstream mapFile;
    //res/saves/hi.txt
    mapFile.open("res/levels/" + std::to_string(num) + ".txt");
    for (int y = 0; y < 110; y++)
    {
        for (int x = 0; x < 110; x++)
        {
            mapFile.get(tile);
            switch (tile)
            {
                
                case '0':
                    map[y][x] = &tiles[0];
                    break;
                case '1':
                    map[y][x] = &tiles[1];
                    break;
                case '2':
                    map[y][x] = &tiles[2];
                    break;
                case '3':
                    map[y][x] = &tiles[3];
                    break;
                case '4':
                    map[y][x] = &tiles[4];
                    break;
                case '5':
                    map[y][x] = &tiles[5];
                    break;
                case '6':
                    map[y][x] = &tiles[6];
                    break;
                case '7':
                    map[y][x] = &tiles[8];
                    break;
                case '9':
                    map[y][x] = &tiles[9];
                    break;
                case 'a':
                    map[y][x] = &tiles[10];
                    break;
                default:
                    std::cout << "ERROR: INVALID MAP FILE" << std::endl;
            }

            mapFile.ignore();
        }
    }
    mapFile.close();

    
}

void World::update(Camera camera, GraphicsManager& window)
{

    if (!(loaded_map)) return;
    day_night += 1;
    if (day_night == 18000) is_day = false;
    if (day_night == 36000) 
    {
        is_day = true;
        day_night = 0;
        //reload berrys:
        for (int row = 0; row < 110; row++)
        {
            for (int col = 0; col < 110; col++)
            {
                if (map[row][col]->getId() == 2)
                {
                    int rand_num = rand() % 2;
                    if (rand_num == 1)
                    {
                        map[row][col] = &tiles[6];
                    }
                }
            }
        }
    }

    for (int row = 0; row < 110; row++)
    {
        for (int col = 0; col < 110; col++)
        {
            if (!isOnScreen(Vector2f(col*128-camera.getPos().x, row*128-camera.getPos().y))) continue;
            SDL_Texture* t = map[row][col]->getTexture();
            Vector2f pos = Vector2f(col*128, row*128);
            window.renderRelativeToCamera(camera, pos, Vector2f(128,128), t);

        }
    }
}

bool World::resolveCollision(Vector2f pos, int size, Camera camera, Vector2f vel)
{
    for (int row = 0; row < 110; row++)
    {
        for (int col = 0; col < 110; col++)
        {
            if (!isOnScreen(Vector2f(col*128-camera.getPos().x, row*128-camera.getPos().y))) continue;
            if ((map[row][col]->isSolid()) && (map[row][col]->isCircle()))
            {
                int d_x, d_y;
                d_x = (col*128+64-camera.getPos().x-vel.x)-(pos.x+32);
                d_y = (row*128+64-camera.getPos().y-vel.y)-(pos.y+32);
                float distance = sqrt((d_x*d_x)+(d_y*d_y));
                if (distance <= size/2+64)
                {
                    return true;
                }
            }
            else if (map[row][col]->isSolid())
            {
                int r2x, r2y;
                r2x = col*128-camera.getPos().x-vel.x;
                r2y = row*128-camera.getPos().y-vel.y;
                if (pos.x + size >= r2x &&
                    pos.x <= r2x + 128 &&
                    pos.y + size >= r2y &&
                    pos.y <= r2y + 128) {
                    return true;
                }
                    
            }
            
        }
    }
    return false;
}

bool World::isOnScreen(Vector2f xy)
{
    if ((xy.x > 1280)||(xy.x < -150))
    {
        return false;
    }
    if ((xy.y > 1280)||(xy.y < -150))
    {
        return false;
    }
    return true;
    
}

int World::hitObject(Vector2f pos, Camera& camera)
{
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse, &yMouse);
    for (int row = 0; row < 110; row++)
    {
        for (int col = 0; col < 110; col++)
        {
            if (!isOnScreen(Vector2f(col*128-camera.getPos().x, row*128-camera.getPos().y))) continue;
            if (map[row][col]->isSolid())
            {
                int d_x, d_y;
                d_x = (col*128+64-camera.getPos().x)-(pos.x+32);
                d_y = (row*128+64-camera.getPos().y)-(pos.y+32);
                float distance = sqrt((d_x*d_x)+(d_y*d_y));
                if (distance <= 128)
                {
                    float angle_to_mouse, angle_to_object;
                    
                    angle_to_mouse = atan2(yMouse-pos.y, xMouse-pos.x)*57.2957795131;
                    angle_to_object = atan2(row*128-camera.getPos().y-pos.y, col*128-camera.getPos().x-pos.x)*57.2957795131;
                    if (fabs(angle_to_mouse-angle_to_object) < 90)
                    {
                        last_hit_tile.x = row;
                        last_hit_tile.y = col;
                        return map[row][col]->getId();
                    }
                }
            }            

        }
    }
    
    return tiles[0].getId();
}


void World::setTile(Vector2f tile, int id)
{
    map[(int)tile.x][(int)tile.y] = &tiles[id];
}

int World::getTileIdAt(Vector2f pos, Camera& cam)
{
    int row = (pos.y + cam.getPos().y)/128;
    int col = (pos.x + cam.getPos().x)/128;
    return map[row][col]->getId();
}

void World::save(const char* p_file)
{
    std::ofstream file;
    file.open(p_file);

    for (int row = 0; row < 110; row++)
    {
        for (int col = 0; col < 110; col++)
        {
            
            std::string c;
            if (map[row][col]->getId() == 10)
            {
                file.write("a,", 2);
            }
            else
            {
                c = std::to_string(map[row][col]->getId()) + ",";
                file.write(c.c_str(), 2);
            }
            
            
        }
    }
    
    file.close();
}

void World::unloadMap()
{

    for (int i = 0; i < 11; i++)
    {
        SDL_DestroyTexture(textures[i]);
    }
    loaded_map = false;
}

