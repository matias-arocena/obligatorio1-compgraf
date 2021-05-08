#include "CubeObject.h"

#include <iostream>

CubeObject::CubeObject(bool showTexture) : showTexture{ showTexture } {
	model = new Model(true);
	model->loadMesh("../assets/cube/cube.obj");
	hitbox = model->getHitBox();
	doScale(Vector3(0.5, 0.5, 0.5));
}

CubeObject::~CubeObject()
{
	delete model;
}

void CubeObject::render()
{
	if (updateShowTexture) {
		model->setShowTextrue(showTexture);
	}

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(scale.x, scale.y, scale.z);
	model->render();
	glPopMatrix();
}

void CubeObject::setShowTexture(bool showTexture)
{
	this->showTexture = showTexture;
	updateShowTexture = true;
}
