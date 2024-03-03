#pragma once
#include "Math.hpp"

struct Plant
{
public:
    Plant(int type_id, int growth_stage, Vector2f p_pos)
    :id(type_id), stage(growth_stage), pos(p_pos)
    {}
    void grow() {stage += 1;}
    int getStage() {return stage;};
private:
    int id;
    int stage;
    Vector2f pos;
};