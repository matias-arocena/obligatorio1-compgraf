#pragma once
#include "GameObject.h"

class Player : public GameObject
{
	public:
		Player();
		void update();
		void render();
		void destroy();


		
	private:
		const float SPEED = 5;

		bool pressedButtons[4] = { false, false, false, false };
		const int FORWARD = 0;
		const int BACK = 1;
		const int LEFT = 2;
		const int RIGHT = 3;

		void updateVel();
};

