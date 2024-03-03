#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "WorldTile.hpp"
#include "GraphicsManager.hpp"
#include "Camera.hpp"

class World
{
public:
    World();
    void loadMap(int num, GraphicsManager& window);
    void update(Camera camera, GraphicsManager& window);
    //Returns whether circular entity collided with world.
    bool resolveCollision(Vector2f pos, int size, Camera camera, Vector2f vel);
    //Returns id of object hit
    int hitObject(Vector2f pos, Camera& camera);
    bool getIsDay() {return is_day;}
    void unloadMap();
    //Sets a tile of the map. x = row, y = column
    void setTile(Vector2f tile, int id);
    WorldTile* getTile(int id) {return &tiles[id];}
     //for berry bush collision;
    int getTileIdAt(Vector2f pos, Camera& cam);
    Vector2f last_hit_tile;
    //save evenrything
    void save(const char* p_file);
    int getCurrentMapId() {return current_map;}
    void onHit(Camera& cam);

    
private:

    int current_map;
    bool loaded_map;
    WorldTile* map[110][110];
    bool isOnScreen(Vector2f xy);
    SDL_Texture* textures[15];
    //0 < dn < 18000 = day     18001 < dn < 36000 = night
    int day_night;
    bool is_day;

    WorldTile tiles[15];

};