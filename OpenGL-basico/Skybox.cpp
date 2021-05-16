#include "Skybox.h"
#include "LevelState.h"

Skybox::Skybox(LevelState* level) : level { level }
{
	loadModel("../assets/skybox/skybox.obj");
	doScale(Vector3(1, 1, 1) * 30);
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

