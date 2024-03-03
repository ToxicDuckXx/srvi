#pragma once

#include <iostream>
#include <cmath>

struct Vector2f
{
    Vector2f()
    :x(0.0f), y(0.0f)
    {}

    Vector2f(float p_x, float p_y)
    :x(p_x), y(p_y)
    {}

    void print()
    {
        std::cout << x << ", " << y << std::endl;
    }

    float x, y;
    void normalize()
    {
        if (x == 0 && y == 0) {return;}
        float m = sqrt(x*x + y*y);
        x = x/m;
        y = y/m;
    }
};

struct Vector2b
{
    Vector2b()
    :x(true), y(true)
    {}

    Vector2b(bool p_x, bool p_y)
    :x(p_x), y(p_y)
    {}

    bool x, y;
};
