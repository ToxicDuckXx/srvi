#include "Camera.hpp"

Camera::Camera(Vector2f initial_pos)
{
    pos = initial_pos;
    vel.x = 0;
    vel.y = 0;
}

Vector2f Camera::getPos()
{
    return pos;
}

void Camera::setPos(Vector2f p_pos)
{
    pos = p_pos;
}

void Camera::centerOnPos(Vector2f p_pos, int screen_width, int screen_height)
{
    pos.x = p_pos.x - screen_width/2;
    pos.y = p_pos.y - screen_height/2;
}

void Camera::update()
{
    pos.x = pos.x + vel.x;
    pos.y = pos.y + vel.y;
}
