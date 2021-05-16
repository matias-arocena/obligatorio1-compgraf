#pragma once
#include "GameObject.h"

class LevelState;

class Skybox :
    public GameObject
{
    LevelState* level;
public:
    Skybox(int rows, LevelState* level);
    void update();
    void render();
    bool isInside(GameObject* entity);
};

