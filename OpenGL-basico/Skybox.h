#pragma once
#include "GameObject.h"

class LevelState;

class Skybox :
    public GameObject
{
    LevelState* level;
public:
    Skybox(LevelState* level);
    void update();
};

