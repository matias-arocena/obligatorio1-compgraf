#pragma once
#include "GameObject.h"

struct EnemyData {
    std::string path;
    float scale;
    float yStart;
    EnemyData(std::string path, float scale, float yStart) :
        path{ path }, scale{ scale }, yStart{ yStart }{};
};

class Enemy :
    public GameObject
{
    int enemyId;
    bool right;
public:
    static std::vector<EnemyData> enemies;
    Enemy(int enemyId, int row, bool right, float vel, float startingX);
    void update();
    void render();
    void setShowTexture(bool showTexture);
    float getYStart();
};

