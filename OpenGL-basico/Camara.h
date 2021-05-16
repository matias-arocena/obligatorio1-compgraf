#pragma once
#include "GameObject.h"

class Camara : public GameObject 
{
	public:
		/*Camara();*/
		void update();
		void onEvent(SDL_Event aEvent);
		GameObject* getObjectToFollow();
		void setObjectToFollow(GameObject *player);
		int state = ISOMETRIC;
		const int ISOMETRIC = 0;
	private:
		const int FOLLOW = 1;
		GameObject *objectToFollow;
		Vector3 offSet = Vector3(-5.0f, -5.0f, -5.0f);
};
