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
	private:
		int state = ISOMETRIC;
		const int ISOMETRIC = 0;
		const int FOLLOW = 1;
		GameObject *objectToFollow;
		Vector3 offSet = (0, 0, 0);
};
