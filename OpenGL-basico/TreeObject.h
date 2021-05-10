#pragma once
#include "GameObject.h"

class TreeObject :
    public GameObject
{
public:
    TreeObject();
    void render();
    void update();
};

