// #include "DragonLair.hpp"

// void DragonLair::loadLair(GraphicsManager& window)
// {
//     lair_tex = window.loadTexture("res/dragon_lair.png");
// }

// void DragonLair::update(GraphicsManager& window, Camera& cam, bool is_winter)
// {
//     if ((cam.getPos().x < 2000) && (cam.getPos().y < 1500) && (is_winter))
//     {
//         window.renderRelativeToCamera(cam, Vector2f(0,0), Vector2f(300,300), lair_tex);
//     }
// }

// void DragonLair::onDragDeath(World& world)
// {
//     world.setTile(Vector2f(4, 4), 11);
// }
