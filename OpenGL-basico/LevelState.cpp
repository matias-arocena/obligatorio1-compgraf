#include "LevelState.h"

#include "Enemy.h"

#include <iostream>

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

//	loadLevel(test);

	player = new Player();
	player->setTileMap(tileMap);

	Enemy* enemy = new Enemy();
	enemy->setPos(Vector3(0, -enemy->getHitBox()->yMin, -5));
//	enemy->setPos(Vector3(-7, 0.5-enemy->getHitBox()->yMin, -5));
//	enemy->setVel(Vector3(1, 0, 0));
	entities.push_back(enemy);
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
					isPaused = !isPaused;
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
}

void LevelState::render()
{
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
