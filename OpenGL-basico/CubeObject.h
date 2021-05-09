#pragma once
#include "GameObject.h"

#include "Model.h"

class CubeObject :
    public GameObject
{
    bool showTexture, updateShowTexture, enemy, hitEnemy, blockFront, blockBack, blockLeft, blockRight, blockUp, blockDown;
public:
    CubeObject(bool showTexture = true, bool isEnemy = false);
    ~CubeObject();
    void update();
    void setVel(Vector3 vel);
    void render();
    void setShowTexture(bool showTexture);
};

