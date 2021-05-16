#pragma once
#include "GameState.h"
#include <vector>

#include "Player.h"
#include "Tile.h"
#include "Skybox.h"

class LevelState : public GameState
{
	public:
		LevelState();
		void init();
		void onEvent(SDL_Event aEvent);
		void update();
		void render();
		void destroy();
		Player* getPlayer();

	private:
		bool showWireframe = false;
		bool updateWireframe = false;
		bool showTexture = true;
		bool showHitbox = false;
		bool showLight = true;

		Player* player;
		Skybox* skybox;
		vector<GameObject*> entities;
		vector<vector<Tile*>> tileMap;
		void loadLevel(vector<vector<int>> aMap);
		void spawnEnemies(vector<vector<int>> enemies);
		void showFog();
		int score = 0;
		int maxPlayerY = 0;
};

