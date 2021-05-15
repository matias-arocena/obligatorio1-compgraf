#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <stdio.h>
#include "Camara.h"
#include <gl/GLU.h>

using namespace std;

//Camara::Camara()
//{ }

GameObject* Camara::getObjectToFollow() { return objectToFollow; }

void Camara::setObjectToFollow(GameObject* player) {
	objectToFollow = player;
	gluLookAt(getPos().x - offSet.x, getPos().y - offSet.y, getPos().z - offSet.z, 0, 0, 0, 0, 1, 0);
}

void Camara::update()
{
	//cout << "Camara coso";
	float x_focus = 0;
	float y_focus = 0;
	float z_focus = 0;

	if (objectToFollow != NULL) {
		x_focus = objectToFollow->getPos().x;
		z_focus = objectToFollow->getPos().z;

		setPos(Vector3(objectToFollow->getPos().x, 0.0f, objectToFollow->getPos().z));
	}	

	//cout << getPos().x;
	//cout << getPos().y;
	//cout << getPos().z << endl;

	//cout << x_focus;
	//cout << z_focus << endl;

	cout << getPos().x;
	cout << getPos().y;
	cout << getPos().z << endl;

	//GameObject::update();

	float input_x = getPos().x - offSet.x;
	float input_y = getPos().y - offSet.y;
	float input_z = getPos().z - offSet.z;

	if (input_x + offSet.x != x_focus) {
		cout << "kill me" << input_x + offSet.x - x_focus << endl;
	}

	gluLookAt(input_x , input_y, input_z, x_focus, 0, z_focus, 0, 1, 0);
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
			state = (state + 1) % 2;

			if (state == ISOMETRIC) {
				offSet = Vector3(-20, -20, -20);

			}
			if (state == FOLLOW) {
				//Calculo de rotacion
				// newX = x cos(angulo) - y sen(angulo)
				// newY = y sen(angulo) + x cos(angulo)
				// 
				//offSet = Vector3(getPos().x * cos(getRot().y) - getPos().z * sin(getRot().y) - 25, -25, getPos().z * sin(getRot().y) + getPos().z * cos(getRot().y) - 25);		
			}


			break;
		}
		break;
	}
}

