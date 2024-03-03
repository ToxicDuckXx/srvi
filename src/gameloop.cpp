#include "GameLoop.hpp"
#include "World.hpp"
#include "Math.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "WolfAi.hpp"
#include "Monster.hpp"
#include "Breed.hpp"
#include "WolfAttack.hpp"
#include "MonsterManager.hpp"
#include "MiniMap.hpp"

void GameLoop(GraphicsManager window)
{
    SDL_Event event;
    bool gameRunning = true;

    SDL_Texture* night_tex = window.loadTexture("res/night.png");

    World world = World();
    Camera camera = Camera(Vector2f(0,0));
    camera.setPos(Vector2f(100, 2000));
    SDL_Texture* player_tex = window.loadTexture("res/player.png");

    MonsterManager monster_manager = MonsterManager(window);

    MiniMap mini_map = MiniMap(window);

    world.loadMap(1, window);
    Vector2f player_vel;
    Player player = Player(player_tex, window);

    //DragonLair lair = DragonLair()
    std::cout << "GAME IS STARTING PLZ WORKD" << std::endl;
    while(gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
                world.save("res/saves/hi.txt");
                player.save();
            }
            else if (event.type == SDL_KEYDOWN)
            {
                player.onPressKey(event.key.keysym.sym, window);
                switch (event.key.keysym.sym)
                {
                case SDLK_d:
                    player_vel.x = 1;
                    break;
                case SDLK_a:
                    player_vel.x = -1;
                    break;
                case SDLK_w:
                    player_vel.y = -1;
                    break;
                case SDLK_s:
                    player_vel.y = 1;
                    break;
                
                default:
                    break;
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_a:
                case SDLK_d:
                    player_vel.x = 0;
                    break;
                case SDLK_s:
                case SDLK_w:
                    player_vel.y = 0;
                    break;
                
                default:
                    break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                player.onPress(world, camera, window, monster_manager);
            }
        }
        camera.update();
        window.clearWindow();
        world.update(camera, window);
        player.update(player_vel, camera, window, world);
        monster_manager.update(camera, world, window, player);
        //lair.update(window, camera, player, world);
        mini_map.update(camera.getPos(), window, world.getCurrentMapId());
        if (!(world.getIsDay())) window.render(Vector2f(0,0), Vector2f(1280,720),night_tex);
        //do stuff (window.render)
        window.display();
    
    }

}