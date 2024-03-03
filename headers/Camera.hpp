#pragma once
#include "Math.hpp"

class Camera
{
public:
    Camera(Vector2f initial_pos);
    Vector2f getPos();
    void setPos(Vector2f p_pos);
    void centerOnPos(Vector2f p_pos, int screen_width, int screen_height);
    void update();
    Vector2f vel;
private:
    Vector2f pos;
};