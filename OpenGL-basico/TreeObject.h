#pragma once
#include "GameObject.h"

#include <memory>

#include "Model.h"

class TreeObject :
    public GameObject
{
public:
    TreeObject();
    ~TreeObject();
    void render();
    void update();
};

