#pragma once
#include "GameObject.h"

#include "Model.h"

class CubeObject :
    public GameObject
{
    bool showTexture, updateShowTexture;;
public:
    CubeObject(bool showTexture = true);
    ~CubeObject();
    void render();
    void setShowTexture(bool showTexture);
};

