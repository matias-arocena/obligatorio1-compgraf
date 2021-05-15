#include "Player.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include "Game.h"

Player::Player()
{
	setAccel(Vector3(0,-20,0));
}

void Player::update()
{
	if (getPos().y <= 0 && curTileWalkable())
	{
		setVel(Vector3(getVel().x, 10, getVel().z));
	}
	
	GameObject::update();
}

void Player::render()
{
	glPushMatrix();
	glTranslatef(getPos().x, getPos().y, getPos().z);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f( + 1.,  0.,  + 0.);
	glVertex3f( - 1.,  0.,  + 0.);
	glVertex3f( + 0.,  + 2.,  + 0.);
	glEnd();

	/*glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);*/

	glPopMatrix();
}

void Player::destroy()
{
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
		case SDLK_a:
			setRot( (getRot().x, getRot().y + 1, getRot().z) );
			break;
		case SDLK_d:
			setRot((getRot().x, getRot().y - 1, getRot().z));
			break;

		updateVel();

		// cout << endl;

		break;
	}
}

void Player::setTileMap(vector<vector<Tile*>> aMap)
{
	tileMap = aMap;
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

	setVel(dir * SPEED + Vector3(0, getVel().y, 0));
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
