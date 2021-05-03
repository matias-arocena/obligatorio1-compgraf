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
}

void Player::update()
{

	//MANEJO DE EVENTOS
	SDL_Event evento;
	while (SDL_PollEvent(&evento))
	{
		switch (evento.type)
		{
			case SDL_KEYDOWN:
				switch (evento.key.keysym.sym)
				{
					case SDLK_UP:
						pressedButtons[FORWARD] = true;
						break;

					case SDLK_DOWN:
						pressedButtons[BACK] = true;
						break;

					case SDLK_LEFT:
						pressedButtons[LEFT] = true;
						break;

					case SDLK_RIGHT:
						pressedButtons[RIGHT] = true;
						break;
				}

				updateVel();

				break;

			case SDL_KEYUP:
				switch (evento.key.keysym.sym)
				{
					case SDLK_UP:
						pressedButtons[FORWARD] = false;
						break;

					case SDLK_DOWN:
						pressedButtons[BACK] = false;
						break;

					case SDLK_LEFT:
						pressedButtons[LEFT] = false;
						break;

					case SDLK_RIGHT:
						pressedButtons[RIGHT] = false;
					break;
				}

				updateVel();

				break;
		}

	}
	//FIN MANEJO DE EVENTOS
	
	GameObject::update();
}

void Player::render()
{
	glPushMatrix();
	glTranslatef(getPos().x, getPos().y, getPos().z);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f( + 1.,  - 1.,  + 0.);
	glVertex3f( - 1.,  - 1.,  + 0.);
	glVertex3f( + 0.,  + 1.,  + 0.);
	glEnd();
	glPopMatrix();
}

void Player::destroy()
{
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

	setVel(dir * SPEED);
}