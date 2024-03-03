#include "GraphicsManager.hpp"
#include <iostream>
#include <cmath>

GraphicsManager::GraphicsManager(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == NULL)
    {
        std::cout << "Window failed to innit Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    num_bitmap = loadTexture("res/number_bitmap.png");

}

SDL_Texture* GraphicsManager::loadTexture(const char* p_filePath)
{

    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if (texture == NULL){
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    }

    return texture;
    // if (!(PHYSFS_exists(p_filePath))) std::cout << "Can't find texture" << std::endl;
    // SDL_RWops* rw;
    // rw = PHYSFSRWOPS_openRead(p_filePath);
    // SDL_Texture* texture = NULL;
    // texture = IMG_LoadTexture_RW(renderer, rw, 0);
    // return texture;

}

void GraphicsManager::destroyWindow()
{
    SDL_DestroyWindow(window);
}

void GraphicsManager::clearWindow()
{
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
}

void GraphicsManager::display()
{
    SDL_RenderPresent(renderer);
}
//size: x=width, y=height
void GraphicsManager::render(Vector2f pos, Vector2f size, SDL_Texture* tex)
{
    SDL_Rect dst;
    dst.x = pos.x;
    dst.y = pos.y;
    dst.w = size.x;
    dst.h = size.y;
    SDL_RenderCopy(renderer, tex, NULL, &dst);
}

void GraphicsManager::renderBitmapNumber(Vector2f pos, int num, int size)
{
    int n = num;
    int pos_x = 0;
    
    while (n)
    {
        int digit = n % 10;
        SDL_Rect dst;
        SDL_Rect src;
        dst.x = pos.x + pos_x;
        dst.y = pos.y;
        dst.w = size;
        dst.h = size;
        src.x = digit * 32;
        src.y = 0;
        src.w = 32;
        src.h = 32;
        
        SDL_RenderCopy(renderer, num_bitmap, &src, &dst);
        n /= 10;
        pos_x -= 9;
    }
}

void GraphicsManager::renderRelativeToCamera(Camera camera, Vector2f pos, Vector2f size, SDL_Texture* tex)
{
    SDL_Rect dst;
    dst.x = pos.x - camera.getPos().x;
    dst.y = pos.y - camera.getPos().y;
    dst.w = size.x;
    dst.h = size.y;
    SDL_RenderCopy(renderer, tex, NULL, &dst);
}

void GraphicsManager::renderTwordsCurser(Vector2f pos, Vector2f size, SDL_Texture* tex, Vector2f point)
{
    
    SDL_Rect dst;
    dst.x = pos.x;
    dst.y = pos.y;
    dst.w = size.x;
    dst.h = size.y;
    int xMouse, yMouse;
    double angle;
    SDL_GetMouseState(&xMouse, &yMouse);
    angle = atan2(yMouse-pos.y, xMouse-pos.x)*57.2957795147+90;
    if (point.x == 0) SDL_RenderCopyEx(renderer, tex, NULL, &dst, angle, NULL, SDL_FLIP_NONE); 
    else{
        SDL_Point p = {(int)point.x, (int)point.y};
        SDL_RenderCopyEx(renderer, tex, NULL, &dst, angle, NULL, SDL_FLIP_NONE); 
    }
      
}

void GraphicsManager::renderEx(Vector2f pos, Vector2f size, SDL_Texture* tex, float angle, Vector2f rotate_point)
{
    SDL_Rect dst;
    dst.x = pos.x;
    dst.y = pos.y;
    dst.w = size.x;
    dst.h = size.y;
    SDL_Point p = {(int)rotate_point.x, (int)rotate_point.y};
    SDL_RenderCopyEx(renderer, tex, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}

void GraphicsManager::renderBar(Vector2f pos, int filled_amount, int r, int g, int b, SDL_Texture* bar_tex)
{
    SDL_Rect rect;
    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = filled_amount;
    rect.h = 40;
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
    rect.w = 200;
    SDL_RenderCopy(renderer, bar_tex, NULL, &rect);
    
}

void GraphicsManager::renderRelativeToCameraEx(Camera camera, Vector2f pos, Vector2f size, SDL_Texture* tex, float angle)
{
    SDL_Rect dst;
    dst.x = pos.x - camera.getPos().x;
    dst.y = pos.y - camera.getPos().y;
    dst.w = size.x;
    dst.h = size.y;
    SDL_RenderCopyEx(renderer, tex, NULL, &dst, angle, NULL, SDL_FLIP_NONE);
}

void loadTextureFromPhy(const char* file_path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(NULL, NULL);

    if (texture == NULL){
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
    }

    return;
    
}

SDL_Texture* GraphicsManager::loadTextureSur(const char* filename)
{

}

SDL_Surface* GraphicsManager::Image_Load_LZ4_RW(SDL_RWops* src, int freesrc)
{
    // Uint16 width;
    // Uint16 height;
    // Uint32 surface_format;
    // int compressed_size;
    // mtar_t tar;
    // mtar_header_t h;
    // char* p;

    // mtar_open(&tar, "assets.tar", "r");

    // mtar_find(&tar, "test.png", &h);
    // p = (char*)calloc(1, h.size + 1);
    // mtar_read_data(&tar, p, h.size);
    
}