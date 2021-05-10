#pragma once
#include "GameObject.h"

class CubeObject :
    public GameObject
{
    bool enemy, hitEnemy, blockFront, blockBack, blockLeft, blockRight, blockUp, blockDown;
public:
    CubeObject(bool isEnemy = false);
    void update();
    void setVel(Vector3 vel);
    void render();
    void setShowTexture(bool showTexture);
};

