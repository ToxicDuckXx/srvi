#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Math.hpp"
#include "Camera.hpp"
#include <SDL_ttf.h>
#include <map>

class GraphicsManager
{
public:
    GraphicsManager(const char* p_title, int p_w, int p_h);
    SDL_Texture* loadTexture(const char* p_file_path);
    SDL_Texture* loadTextureSur(const char* p_file_path);
    void destroyWindow();
    void clearWindow();
    void display();
    void render(Vector2f pos, Vector2f size, SDL_Texture* tex);
    void renderRelativeToCamera(Camera camera, Vector2f pos, Vector2f size, SDL_Texture* tex);
    void renderTwordsCurser(Vector2f pos, Vector2f size, SDL_Texture* tex, Vector2f point);
    void renderEx(Vector2f pos, Vector2f size, SDL_Texture* tex, float angle, Vector2f rotate_point);
    void renderBar(Vector2f pos, int filled_amount, int r, int g, int b, SDL_Texture* bar);
    void renderRelativeToCameraEx(Camera camera, Vector2f pos, Vector2f size, SDL_Texture* tex, float angle);
    void renderBitmapNumber(Vector2f pos, int num, int size);
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* num_bitmap;
    SDL_Surface* Image_Load_LZ4_RW(SDL_RWops* src, int freesrc);
    std::map<int, SDL_Texture*> textures;
};