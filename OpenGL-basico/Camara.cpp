#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <stdio.h>
#include "Camara.h"
#include <gl/GLU.h>

using namespace std;

GameObject* Camara::getObjectToFollow() { return objectToFollow; }

void Camara::setObjectToFollow(GameObject* player) {
	objectToFollow = player;
	gluLookAt(getPos().x - offSet.x, getPos().y - offSet.y, getPos().z - offSet.z, 0, 0, 0, 0, 1, 0);
}

void Camara::update()
{
	if (state == ISOMETRIC) {
		offSet = Vector3(-20, -20, -20);
	}
	if (state == FOLLOW) {
		offSet = Vector3(-0 * cos(getRot().y) - (-10 * sin(getRot().y) ), -0.5, -0 * sin(getRot().y) + (-10) * cos(getRot().y));
	}

	float x_focus = 0;
	float y_focus = 0;
	float z_focus = 0;

	if (objectToFollow != NULL) {
		x_focus = objectToFollow->getPos().x;
		z_focus = objectToFollow->getPos().z;

		setPos(Vector3(objectToFollow->getPos().x, 0.0f, objectToFollow->getPos().z));
	}	

	float input_x = getPos().x - offSet.x;
	float input_y = getPos().y - offSet.y;
	float input_z = getPos().z - offSet.z;

	cout << "Posicion Camara" << input_x << " " << input_z << endl;

	gluLookAt(input_x , input_y, input_z, x_focus, 0, z_focus, 0, 1, 0);
}


void Camara::onEvent(SDL_Event aEvent)
{
	switch (aEvent.type)
	{
	case SDL_KEYDOWN:

		break;

	case SDL_KEYUP:

		switch (aEvent.key.keysym.sym)
		{
		case SDLK_v:
			state = (state + 1) % 2;
			break;
		}
		break;
	}
}

