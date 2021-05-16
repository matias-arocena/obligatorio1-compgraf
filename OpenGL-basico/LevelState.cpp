#include "LevelState.h"

#include "Enemy.h"

#include <iostream>
#include "Game.h"

LevelState::LevelState()
{
}

void LevelState::init()
{

	skybox = new Skybox(this);

	vector<vector<int>> test =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},

	};

	vector<vector<int>> spawn =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,2,0,0,0,2,2,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,2,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,0,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,2,2,2,0,0,0,2,0,2,0,0,0,2,0,0,2,2,2,0,0,2,0,0,2,2,0,0,2,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,0,0,1,0,1,1,0,0,1,1,1,1,0,0,0,0,1,0,0,1,1,1,0,0,1,0,0,0,1,0},
		{0,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,2,0,0,2,0,0,2,2,2,2,2,0,0,2,0,0,2,0,2,0,2,2,0,0,0,2,0,0,2,0},
		{1,1,0,0,1,0,1,1,0,0,1,1,1,1,0,0,0,0,1,0,0,1,1,1,0,0,1,0,0,0,1,0},
		{2,0,0,2,2,2,0,0,0,2,0,2,0,0,0,2,0,0,2,2,2,0,0,2,0,0,2,2,0,0,2,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};

	loadLevel(test);
	spawnEnemies(spawn);

	player = new Player();
	player->setTileMap(tileMap);


	Game::inst().cam->setObjectToFollow(player);
}

void LevelState::onEvent(SDL_Event aEvent)
{
	switch (aEvent.type)
	{
		case SDL_KEYDOWN:
			// cout << "Key Down" << endl;
			switch (aEvent.key.keysym.sym)
			{
				case SDLK_p:
					Game::inst().isPaused = !Game::inst().isPaused;
					break;
				case SDLK_w:
					showWireframe = !showWireframe;
					updateWireframe = true;
					break;
				case SDLK_t:
					showTexture = !showTexture;
					player->setShowTexture(showTexture);
					for (auto& e : entities) {
						e->setShowTexture(showTexture);
					}	
					for (int j = 0; j < tileMap.size(); j++)
					{
						for (int i = 0; i < tileMap[j].size(); i++)
						{
							if (tileMap[j][i] != nullptr)
							{
								tileMap[j][i]->setShowTexture(showTexture);
							}
						}
					}
					break;
				case SDLK_h:
					showHitbox = !showHitbox;
					player->setShowHitbox(showHitbox);
					for (auto& e : entities) {
						e->setShowHitbox(showHitbox);
					}
					for (int j = 0; j < tileMap.size(); j++)
					{
						for (int i = 0; i < tileMap[j].size(); i++)
						{
							if (tileMap[j][i] != nullptr)
							{
								tileMap[j][i]->setShowHitbox(showHitbox);
							}
						}
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	player->onEvent(aEvent);
}

void LevelState::update()
{
	if (Game::inst().isPaused) return;

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

	for (auto& e : entities) {
		e->update();
	}

	player->calculateCollisions(entities);
	player->update();

	int curPlayerY = - player->getPos().z / Tile::TILE_WIDTH;
	if (curPlayerY > maxPlayerY)
	{
		score += 1;
		maxPlayerY = curPlayerY;

		cout << score << endl;
	}

	skybox->update();
}

void LevelState::render()
{
	skybox->render();
	glEnable(GL_LIGHTING);
	if (updateWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);
		updateWireframe = false;
	}

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

	for (auto& e : entities) {
		e->render();
	}
	player->render();
	glDisable(GL_LIGHTING);
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

Player* LevelState::getPlayer()
{
	return player;
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

void LevelState::spawnEnemies(vector<vector<int>> enemies)
{
	srand(time(nullptr));
	float maxVel = 20;

	for (int i = 0; i < enemies.size(); i++){
		for (int j = 0; j < enemies[i].size(); j++)
		{
			if (enemies[i][j] == 1)
			{
				entities.push_back(new Enemy(rand() % Enemy::enemies.size(), i, true, i * (maxVel / enemies.size()),  j * 2));
			}
			else if (enemies[i][j] == 2) {
				entities.push_back(new Enemy(rand() % Enemy::enemies.size(), i, false, i * (maxVel / enemies.size()), j * 2));
			}
		}
	}
}
