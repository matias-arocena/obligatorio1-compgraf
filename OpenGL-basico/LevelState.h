#pragma once
#include "GameState.h"
#include <vector>

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
		vector<vector<Tile*>> tileMap;
		void loadLevel(vector<vector<int>> aMap);
};

