#pragma once
#include "GameState.h"
#include "Player.h"

class MovementTestState :
    public GameState
{
    public:
        MovementTestState();
        void init();
        void update();
        void render();
        void destroy();

    private:
        Player* player;
};

