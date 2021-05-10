#pragma once
#include "Vector3.h"
//#include "Game.h"
#include "Model.h"

class Game;

class GameObject
{
	public:
		GameObject()
		{
			pos = Vector3();
			scale = Vector3(1, 1, 1);
			rot = Vector3();
		}

		virtual void update();

		virtual void render() {};

		virtual void destroy() {}

		Vector3 getRot()
		{
			return rot;
		}

		void setRot(Vector3 aVector)
		{
			rot = aVector;
		}

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
		
		HitBox* getHitBox();

		void setAccel(Vector3 aVector)
		{
			accel = aVector;
		}

		Vector3 getAccel()
		{
			return accel;
		}

		virtual void setShowTexture(bool showTexture) {}
		void setCurrentCollisions(std::vector<GameObject*> collisions);
	private:
		Vector3 accel;

	protected:
		Vector3 pos;
		Vector3 vel;
		Vector3 scale;
		Vector3 rot;
		HitBox* hitbox;
		std::vector<GameObject*> currentCollisions;
		Model* model;

		void doScale(Vector3 scale);
};

