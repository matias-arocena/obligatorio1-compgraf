#include "Enemy.h"

#include <iostream>

std::vector<EnemyData> Enemy::enemies = {
	EnemyData("../assets/enemy1.stl", 0.01, 0.5),
	EnemyData("../assets/enemy2.stl", 0.8, 0),
//	EnemyData("../assets/Magellan/Magellan_16.obj", 0.3, 0),
	EnemyData("../assets/enemy3/70m_rev_e.3ds", 0.02, 0),
};

Enemy::Enemy(int enemyId, int row, bool right, float vel, float startingX) {
	loadModel(enemies[enemyId].path);
	doScale(Vector3(1, 1, 1) * enemies[enemyId].scale);
	doRotate(Vector3(0, 1 / (rand() % 3 + 1), 0));
	this->vel = right ? vel : -vel;
	this->right = right;
	pos = Vector3(startingX, enemies[enemyId].yStart-hitbox->yMin, -(row * 2 + 1));
}

void Enemy::update() {
	if (right && pos.x > 31) {
		setPos(Vector3(-31, pos.y, pos.z));
	}
	else if (!right && pos.x < -31) {
		setPos(Vector3(31, pos.y, pos.z));
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

float Enemy::getYStart()
{
	return Enemy::enemies[enemyId].yStart;
}

