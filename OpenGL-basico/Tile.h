#pragma once
#include "GameObject.h"
class Tile :
    public GameObject
{
    public:
        Tile(int aX, int aY);
        void render();

        static const int TILE_WIDTH = 2;
};

