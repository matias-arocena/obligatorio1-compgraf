#include "LevelState.h"

LevelState::LevelState()
{
}

void LevelState::init()
{

	vector<vector<int>> test =
	{
		{1, 1, 1},
		{0, 0, 0},
		{1, 0, 1},
		{0, 0, 0},
		{1, 1, 1}
	};

	loadLevel(test);

	player = new Player();
	player->setTileMap(tileMap);
}

void LevelState::onEvent(SDL_Event aEvent)
{
	switch (aEvent.type)
	{
		case SDL_KEYDOWN:
			// cout << "Key Down" << endl;
			switch (aEvent.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					isPaused = !isPaused;
					break;
			}
			break;
	}

	player->onEvent(aEvent);
}

void LevelState::update()
{
	//MANEJO DE EVENTOS
	SDL_Event evento;
	while (SDL_PollEvent(&evento))
	{
		
	}
	//FIN MANEJO DE EVENTOS

	if (isPaused) return;

	for (int j = 0; j < tileMap.size(); j++)
	{
		for (int i = 0; i < tileMap[j].size(); i++)
		{
			if (tileMap[j][i] != NULL)
			{
				tileMap[j][i]->update();
			}
		}
	}

	player->update();

	int curPlayerY = - player->getPos().z / Tile::TILE_WIDTH;
	if (curPlayerY > maxPlayerY)
	{
		score += 1;
		maxPlayerY = curPlayerY;

		cout << score << endl;
	}
}

void LevelState::render()
{
	for (int j = 0; j < tileMap.size(); j++)
	{
		for (int i = 0; i < tileMap[j].size(); i++)
		{
			if (tileMap[j][i] != NULL)
			{
				tileMap[j][i]->render();
			}
		}
	}

	player->render();
}

void LevelState::destroy()
{
	for (int j = 0; j < tileMap.size(); j++)
	{
		for (int i = 0; i < tileMap[j].size(); i++)
		{
			if (tileMap[j][i] != NULL)
			{
				tileMap[j][i]->destroy();
			}
		}
	}

	player->destroy();
}

void LevelState::loadLevel(vector<vector<int>> aMap)
{
	for (int j = 0; j < aMap.size(); j++)
	{
		tileMap.push_back(vector<Tile*>());
		for (int i = 0; i < aMap[j].size(); i++)
		{
			if (aMap[j][i] == 1)
			{
				tileMap[j].push_back(new Tile(i, j));
			}
			else
			{
				tileMap[j].push_back(NULL);
			}
		}
	}
}
