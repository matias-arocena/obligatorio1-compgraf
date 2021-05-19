#include "Enemy.h"

#include <iostream>

std::vector<EnemyData> Enemy::enemies = {
	EnemyData("../assets/enemy2.stl", 0.8, 0),
	EnemyData("../assets/enemy1/enemy1.3ds", 0.8, 0),
};

Enemy::Enemy(int enemyId, int row, bool right, float vel, float startingX, float boundary) : boundary{ boundary } {
	loadModel(enemies[enemyId].path);
	doScale(Vector3(1, 1, 1) * enemies[enemyId].scale);
	doRotate(Vector3(0, 45 * (rand() % 4), 0));

	this->vel = right ? vel : -vel;
	this->right = right;
	pos = Vector3(startingX, enemies[enemyId].yStart-hitbox->yMin, -(row * 2 + 1));
	
	float maxRotSpeed = 240.0f;
	this->rotVel = Vector3(((float)rand() / (RAND_MAX) - 0.5f) * maxRotSpeed, ((float)rand() / (RAND_MAX) -0.5f) * maxRotSpeed, 0/*((float)rand() / (RAND_MAX) -0.5f) * maxRotSpeed*/);
}

void Enemy::update() {
	if (right && pos.x > boundary) {
		setPos(Vector3(-boundary, pos.y, pos.z));
	}
	else if (!right && pos.x < -boundary) {
		setPos(Vector3(boundary, pos.y, pos.z));
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

