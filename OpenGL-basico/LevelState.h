#pragma once
#include "GameState.h"
#include <vector>

#include "Player.h"
#include "Tile.h"

class LevelState : public GameState
{
	public:
		LevelState();
		void init();
		void onEvent(SDL_Event aEvent);
		void update();
		void render();
		void destroy();

	private:
		bool isPaused = false;

		Player* player;
		vector<GameObject*> entities;
		vector<vector<Tile*>> tileMap;
		void loadLevel(vector<vector<int>> aMap);
		int score = 0;
		int maxPlayerY = 0;
};

