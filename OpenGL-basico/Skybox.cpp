#include "Skybox.h"
#include "LevelState.h"

Skybox::Skybox(LevelState* level) : level { level }
{
	loadModel("../assets/skybox/skybox.obj");
	doScale(Vector3(10, 10, 10));
}

void Skybox::update()
{
	setPos(level->getPlayer()->getPos());
}

