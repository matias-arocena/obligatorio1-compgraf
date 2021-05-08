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
		void update();
		void render();
		void destroy();

	private:
		Player* player;
		vector<vector<Tile*>> tileMap;
		void loadLevel(vector<vector<int>> aMap);
		int score = 0;
		int maxPlayerY = 0;
};

