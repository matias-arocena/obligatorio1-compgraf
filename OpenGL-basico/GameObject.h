#pragma once
#include "Vector3.h"
#include "Game.h"
#include <iostream>
#include <stdio.h>
class GameObject
{
	public:
		GameObject()
		{
			pos = Vector3();
		}

		virtual void update() 
		{
			vel += accel * Game::inst().getDeltaTime();
			pos += vel * Game::inst().getDeltaTime();
		}
		virtual void render() {}
		virtual void destroy() {}

		Vector3 getPos()
		{
			return pos;
		}

		void setPos(Vector3 aVector)
		{
			pos = aVector;
		}

		void setVel(Vector3 aVector)
		{
			vel = aVector;
		}

		Vector3 getVel()
		{
			return vel;
		}

		void setAccel(Vector3 aVector)
		{
			accel = aVector;
		}

		Vector3 getAccel()
		{
			return accel;
		}


	private:
		Vector3 pos;
		Vector3 vel;
		Vector3 accel;
};

