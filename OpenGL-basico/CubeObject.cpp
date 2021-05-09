#include "CubeObject.h"

#include "TreeObject.h"
#include <iostream>

CubeObject::CubeObject(bool isEnemy, bool showTexture) : enemy { isEnemy }, showTexture { showTexture } {
	model = new Model(true);
	model->loadMesh("../assets/cube/cube.obj");
	hitbox = model->getHitBox();
	doScale(Vector3(0.5, 0.5, 0.5));
	hitEnemy = blockFront = blockBack = blockLeft = blockRight = blockUp = blockDown = false;
}

CubeObject::~CubeObject()
{
	delete model;
}

void CubeObject::update() {
	GameObject::update();
	if (!enemy) {
		bool hitEnemyAux, blockFrontAux, blockBackAux, blockLeftAux, blockRightAux, blockUpAux, blockDownAux;
		hitEnemyAux = blockFrontAux = blockBackAux = blockLeftAux = blockRightAux = blockUpAux = blockDownAux = false;

		for (GameObject* c : currentCollisions) {
			if (CubeObject* e = dynamic_cast<CubeObject*>(c)) {
				if (e->enemy) {
					hitEnemyAux = true;
				}
			}
			else if (TreeObject* t = dynamic_cast<TreeObject*>(c)) {
				blockFrontAux = blockFrontAux ? blockFrontAux : pos.z + hitbox->zMax >= c->getPos().z + c->getHitBox()->zMin;
				blockBackAux = blockBackAux ? blockBackAux : pos.z + hitbox->zMin <= c->getPos().z + c->getHitBox()->zMax;
				blockRightAux = blockRightAux ? blockRightAux : pos.x + hitbox->xMax >= c->getPos().x + c->getHitBox()->xMin;
				blockLeftAux = blockLeftAux ? blockLeftAux : pos.x + hitbox->xMin <= c->getPos().x + c->getHitBox()->xMax;
				blockUpAux = blockUpAux ? blockUpAux : pos.y + hitbox->yMax >= c->getPos().y + c->getHitBox()->yMin;
				blockDownAux = blockDownAux ? blockDownAux : pos.y + hitbox->yMin <= c->getPos().y + c->getHitBox()->yMax;
			}
		}
		hitEnemy = hitEnemyAux;
		blockFront = blockFrontAux;
		blockBack = blockBackAux;
		blockRight = blockRightAux;
		blockLeft = blockLeftAux;
		blockUp = blockUpAux;
		blockDown = blockDownAux;
	}
}

void CubeObject::setVel(Vector3 vel) {
	vel.x = blockRight && vel.x > 0 ? 0 : vel.x;
	vel.x = blockLeft && vel.x < 0 ? 0 : vel.x;
	vel.y = blockUp && vel.y > 0 ? 0 : vel.y;
	vel.y = blockDown && vel.y < 0 ? 0 : vel.y;
	vel.z = blockFront && vel.z > 0 ? 0 : vel.z;
	vel.z = blockBack && vel.z < 0 ? 0 : vel.z;

	GameObject::setVel(vel);
}

void CubeObject::render()
{
	if (updateShowTexture) {
		model->setShowTextrue(showTexture);
	}

	if (!hitEnemy) {
		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(scale.x, scale.y, scale.z);
		model->render();
		glPopMatrix();
	}
}

void CubeObject::setShowTexture(bool showTexture)
{
	this->showTexture = showTexture;
	updateShowTexture = true;
}
