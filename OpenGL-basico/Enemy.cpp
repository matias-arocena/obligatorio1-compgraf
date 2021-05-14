#include "Enemy.h"

#include <iostream>

Enemy::Enemy() {
	loadModel("../assets/cube/cube.obj");
	doScale(Vector3(2, 2, 2));
	doRotate(Vector3(0, 45, 0));
}

void Enemy::update() {
	if (pos.x > 10) {
		setPos(Vector3(-10, pos.y, pos.z));
	}
	GameObject::update();
}

void Enemy::render()
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	GameObject::render();
	glPopMatrix();
}

void Enemy::setShowTexture(bool showTexture)
{
	this->showTexture = showTexture;
}
