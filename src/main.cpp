#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "GraphicsManager.hpp"
#include "GameLoop.hpp"
#include "ReadItemFile.hpp"


int main(int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO) > 0) {
        std::cout << "SDL_INNIT HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
    }
    if (!(IMG_Init(IMG_INIT_PNG))) {
        std::cout << "IMG_INNIT FAILED: " << SDL_GetError() << std::endl;
    }
    //PHYSFS_init(*argv);
    //PHYSFS_mount("res/textures.zip", NULL, 1);
    //window specs
    GraphicsManager window("TITLE", 1280, 720);
    
    //register textures with window.loadTexture(p_file_path)
    ReadItemFile::getItems();
    GameLoop(window);

    window.destroyWindow();
    SDL_Quit();
    //PHYSFS_deinit();
    return 0;
}