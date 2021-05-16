#include "Skybox.h"
#include "LevelState.h"

Skybox::Skybox(int rows, LevelState* level) : level { level }
{
	loadModel("../assets/skybox/skybox.obj");
	doScale(Vector3(1, 1, 1) * rows * 1.5);
}


void Skybox::update()
{
	setPos(level->getPlayer()->getPos());
	pos.y = 0;
}

void Skybox::render() {
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	GameObject::render();
	glPopMatrix();
}

bool Skybox::isInside(GameObject* e)
{
	bool collisionX = this->pos.x + this->hitbox->xMax >= e->getPos().x + e->getHitBox()->xMin &&
		this->pos.x + this->hitbox->xMin <= e->getPos().x + e->getHitBox()->xMax;
	bool collisionY = this->pos.y + this->hitbox->yMax >= e->getPos().y + e->getHitBox()->yMin &&
		this->pos.y + this->hitbox->yMin <= e->getPos().y + e->getHitBox()->yMax;
	bool collisionZ = this->pos.z + this->hitbox->zMax >= e->getPos().z + e->getHitBox()->zMin &&
		this->pos.z + this->hitbox->zMin <= e->getPos().z + e->getHitBox()->zMax;
	
	return collisionX && collisionY && collisionZ;
}

