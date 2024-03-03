#pragma once
#include <SDL.h>
#include <SDL_image.h>

class WorldTile
{
public:

    WorldTile(bool p_is_solid, bool p_is_circle, bool p_is_water, SDL_Texture* p_texture, int p_id)
    :is_solid(p_is_solid), is_circle(p_is_circle), is_water(p_is_water), texture(p_texture), id(p_id)
    {}
    WorldTile()
    :is_solid(false), is_circle(false), is_water(false), texture(NULL), id(0)
    {}
    bool isSolid() const {return is_solid;}
    bool isCircle() const {return is_circle;}
    bool isWater() const {return is_water;}
    int getId() const {return id;}
    SDL_Texture* getTexture() {return texture;}
    
private:
    bool is_solid;
    bool is_circle;
    bool is_water;
    int id;
    SDL_Texture* texture;
};