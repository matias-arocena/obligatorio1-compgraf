#pragma once
#include "GameObject.h"
class Tile :
    public GameObject
{
    public:
        Tile(int aX, int aY);
        void render();

    private:
        const float TILE_WIDTH = 2;
};

