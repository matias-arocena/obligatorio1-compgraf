#include "GameObject.h"
#include "Game.h"
#include <iostream>

HitBox* GameObject::getHitBox()
{
    return hitbox;
}

void GameObject::setCurrentCollisions(std::vector<GameObject*> collisions)
{
    currentCollisions = collisions;
}

void GameObject::update()
{
    vel += accel * Game::inst().getDeltaTime();
    pos += vel * Game::inst().getDeltaTime();
}

void GameObject::doScale(Vector3 scale)
{
    hitbox->xMax = hitbox->xMax * scale.x;
    hitbox->xMin = hitbox->xMin * scale.x;
    hitbox->yMax = hitbox->yMax * scale.y;
    hitbox->yMin = hitbox->yMin * scale.y;
    hitbox->zMax = hitbox->zMax * scale.z;
    hitbox->zMin = hitbox->zMin * scale.z;

    this->scale = scale;
}

