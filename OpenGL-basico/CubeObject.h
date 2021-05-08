#pragma once
#include "GameObject.h"

#include "Model.h"

class CubeObject :
    public GameObject
{
public:
    CubeObject();
    ~CubeObject();
    void render();
};

