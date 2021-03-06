#include "Player.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include "Game.h"
#include "Enemy.h"
#include "LevelState.h"

using namespace std;

Player::Player()
{
	loadModel("../assets/player.obj");
	doScale(Vector3(1, 1, 1));
	scaleHitbox(Vector3(0.8, 0.8, 0.8));
	setAccel(Vector3(0,-20,0));
}

void Player::update()
{
	if (Game::inst().getCamara()->state == Game::inst().getCamara()->ISOMETRIC && getRot().y != 0)
	{
		setRot(Vector3(0, 0, 0));
	}

	if (getPos().y <= 0 && getPos().y > -0.5f * Game::inst().gameVelocity && curTileWalkable())
	{
		setVel(Vector3(getVel().x, 10, getVel().z));
		levelState->checkScore();
	}
	
	for (auto& entity : currentCollisions) {
		if (dynamic_cast<Enemy*>(entity) != nullptr) {
			pos.x = 0;
			pos.y = -20;
		}
	}


	GameObject::update();
	
	if (getPos().y <= -4)
	{
		levelState->gameOver();
	}
}

void Player::render()
{
	glPushMatrix();
	glTranslatef(getPos().x, getPos().y, getPos().z);
	glRotatef(180, 0, 1, 0);
	GameObject::render();
	glPopMatrix();
}

void Player::destroy()
{
	GameObject::destroy();
}

void Player::onEvent(SDL_Event aEvent)
{
	switch (aEvent.type)
	{
	case SDL_KEYDOWN:
		// cout << "Key Down" << endl;
		switch (aEvent.key.keysym.sym)
		{
		case SDLK_UP:
			// cout << "Up" << endl;
			pressedButtons[FORWARD] = true;
			break;

		case SDLK_DOWN:
			// cout << "Down" << endl;
			pressedButtons[BACK] = true;
			break;

		case SDLK_LEFT:
			// cout << "Left" << endl;
			pressedButtons[LEFT] = true;
			break;

		case SDLK_RIGHT:
			// cout << "Right" << endl;
			pressedButtons[RIGHT] = true;
			break;
		}

		updateVel();

		// cout << endl;

		break;

	case SDL_KEYUP:

		// cout << "Key Up" << endl;

		switch (aEvent.key.keysym.sym)
		{
		case SDLK_UP:
			// cout << "Up" << endl;
			pressedButtons[FORWARD] = false;
			break;

		case SDLK_DOWN:
			// cout << "Down" << endl;
			pressedButtons[BACK] = false;
			break;

		case SDLK_LEFT:
			// cout << "Left" << endl;
			pressedButtons[LEFT] = false;
			break;

		case SDLK_RIGHT:
			// cout << "Right" << endl;
			pressedButtons[RIGHT] = false;
			break;
		}

		updateVel();

		// cout << endl;

		break;
	case SDL_MOUSEMOTION:
		if (Game::inst().cam->state != Game::inst().cam->ISOMETRIC) {
			doRotate(Vector3(getRot().x, getRot().y + aEvent.motion.xrel * ROTATESPEED, getRot().z));
		};
		
		break;
	
	}

}

void Player::setTileMap(vector<vector<Tile*>> aMap)
{
	tileMap = aMap;
	setPos(Vector3(tileMap[0].size() * Tile::TILE_WIDTH / 2.f, 0, - Tile::TILE_WIDTH / 2.f));
}

void Player::calculateCollisions(vector<GameObject*> entities)
{
	currentCollisions.clear();
	for (auto& e : entities) {
		if (e != this) {
			bool collisionX = this->pos.x + this->hitbox->xMax >= e->getPos().x + e->getHitBox()->xMin &&
				this->pos.x + this->hitbox->xMin <= e->getPos().x + e->getHitBox()->xMax;
			bool collisionY = this->pos.y + this->hitbox->yMax >= e->getPos().y + e->getHitBox()->yMin &&
				this->pos.y + this->hitbox->yMin <= e->getPos().y + e->getHitBox()->yMax;
			bool collisionZ = this->pos.z + this->hitbox->zMax >= e->getPos().z + e->getHitBox()->zMin &&
				this->pos.z + this->hitbox->zMin <= e->getPos().z + e->getHitBox()->zMax;
			
			if (collisionX && collisionY && collisionZ) {
				currentCollisions.push_back(e);
			}
		}
	}
}

void Player::setLevelState(LevelState* aState)
{
	levelState = aState;
}

void Player::updateVel()
{
	Vector3 dir = Vector3();
	if (pressedButtons[FORWARD])
	{
		dir.z -= 1;
	}
	if (pressedButtons[BACK])
	{
		dir.z += 1;
	}
	if (pressedButtons[LEFT])
	{
		dir.x -= 1;
	}
	if (pressedButtons[RIGHT])
	{
		dir.x += 1;
	}

	float angle = getRot().y * M_PI / 180;
	Vector3 angledDir = Vector3(dir.x * cos(angle) + dir.z * sin(angle), 0, -dir.x * sin(angle) + dir.z * cos(angle));

	setVel(angledDir * SPEED + Vector3(0, getVel().y, 0));
}

bool Player::curTileWalkable()
{
	if (tileMap.size() == 0)
		return true;

	int x = getPos().x / Tile::TILE_WIDTH;
	int y = - getPos().z / Tile::TILE_WIDTH;

	if (getPos().z > 0 || y >= tileMap.size() || getPos().x < 0 || x >= tileMap[y].size())
		return false;

	return (tileMap[y][x] != NULL);
}
