#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <stdio.h>
#include "Camara.h"

//Camara::Camara()
//{ }

GameObject Camara::getObjectToFollow() { return objectToFollow; }

void Camara::setObjectToFollow(GameObject player) {
	objectToFollow = player;
}

void Camara::update()
{
	int x_focus = 0;
	int y_focus = 0;
	int z_focus = 0;

	if (objectToFollow !== NULL) {
		x_focus = objectToFollow.getPos().x;
		z_focus = objectToFollow.getPos().z;
	}	

	gluLookAt(getPos().x - offSet.x, getPost().y - offSet.y, getPos().z - offSet.z, x_focus, 0, z_focus, 0, 1, 0);

	GameObject::update();
}


void Camara::onEvent(SDL_Event aEvent)
{
	switch (aEvent.type)
	{
	case SDL_KEYDOWN:

		break;

	case SDL_KEYUP:

		// cout << "Key Up" << endl;

		switch (aEvent.key.keysym.sym)
		{
		case SDLK_v:
			state = (state + 1) % 3;

			if (state === ISOMETRIC) {
				offSet = (-25, -25, -25);
			}
			if (state === FOLLOW) {
				//Calculo de rotacion
				// newX = x cos(angulo) - y sen(angulo)
				// newY = y sen(angulo) + x cos(angulo)
				offSet = (getPos().x * cos(getRot().y) - getPos().z * sin(getRot().y) - 25, -25, getPos().z * sin(getRot().y) + getPos().z * cos(getRot().y) - 25);
			}


			break;
		}
		break;
	}
}

