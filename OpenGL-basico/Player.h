#pragma once
#include "GameObject.h"
#include <vector>
#include "Tile.h"
#include "SDL.h"
#include "LevelState.h"

using namespace std;

class LevelState;

class Player : public GameObject
{
	public:
		Player();
		void update();
		void render();
		void destroy();
		void onEvent(SDL_Event aEvent);

		void setTileMap(vector<vector<Tile*>> aMap);
		void calculateCollisions(vector<GameObject*> entities);

		void setLevelState(LevelState* aState);
		
	private:
		const float SPEED = 5;

		bool pressedButtons[4] = { false, false, false, false };
		const int FORWARD = 0;
		const int BACK = 1;
		const int LEFT = 2;
		const int RIGHT = 3;
		const float ROTATESPEED = -1;

		void updateVel();

		vector<vector<Tile*>> tileMap;
		bool curTileWalkable();

		vector<GameObject*> currentCollisions;

		LevelState* levelState;
};

