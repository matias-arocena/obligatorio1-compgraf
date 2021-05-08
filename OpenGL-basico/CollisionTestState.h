#pragma once
#include "GameState.h"

#include <vector>
#include <string>

#include "GameObject.h"

class CollisionTestState :
    public GameState
{
    bool showWireframe, updateWireframe;
    std::vector<GameObject*> entities;
public:
    CollisionTestState();
    void init();
    void update();
    void render();
private:
    std::vector<GameObject*> getCollisions(GameObject* object);
    bool collides(GameObject* o1, GameObject* o2);
};

