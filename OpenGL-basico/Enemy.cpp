#include "Enemy.h"

#include <iostream>

Enemy::Enemy() {
	loadModel("../assets/cube/cube.obj");
	doScale(Vector3(0.5, 0.5, 0.5));
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
	glScalef(scale.x, scale.y, scale.z);
	GameObject::render();
	glPopMatrix();
}

void Enemy::setShowTexture(bool showTexture)
{
	this->showTexture = showTexture;
}
