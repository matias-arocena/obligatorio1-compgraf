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

	private:
		Vector3 pos;
		Vector3 vel;
};

