#include "LevelState.h"

#include "Enemy.h"

#include <iostream>
#include <GL/freeglut.h>
#include "Game.h"


void dibuHUD(int score, int seconds) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 640, 1.0, 480);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glRasterPos2i(25, 450);
	char score_string[1000];
	sprintf_s(score_string, "%s%d", "Puntaje: ", score);
	const unsigned char* ss = reinterpret_cast<const unsigned char*>(score_string);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, ss);

	glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
	glRasterPos2i(25, 430);
	char time_string[1000];
	sprintf_s(time_string, "%s%d", "Tiempo: ", seconds);
	const unsigned char* ts = reinterpret_cast<const unsigned char*>(time_string);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, ts);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

LevelState::LevelState()
{
}

void LevelState::init()
{

	skybox = new Skybox(10, this);

	vector<vector<int>> test =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},		
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	vector<vector<int>> spawn =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
		{2, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 2, 2, 0, 0, 2, 2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0},
		{0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
		{0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 2, 0, 0, 2, 2, 0, 0, 2, 2, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 2, 0, 0, 2, 0, 0, 0, 2, 2},
		{0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0},
		{0, 2, 2, 0, 0, 0, 2, 0, 2, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
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
				case SDLK_l:
					showLight = !showLight;
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
	dibuHUD(score, Game::inst().seconds);
	skybox->render();
	if (showLight) {
		glEnable(GL_LIGHTING);
		showFog();
	}
	else {
		glDisable(GL_FOG);
	}

	if (updateWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, showWireframe ? GL_LINE : GL_FILL);
		updateWireframe = false;
	}

	for (int j = 0; j < tileMap.size(); j++)
	{
		for (int i = 0; i < tileMap[j].size(); i++)
		{
			if (tileMap[j][i] != NULL && skybox->isInside(tileMap[j][i]))
			{
				tileMap[j][i]->render();
			}
		}
	}

	for (auto& e : entities) {
		if (skybox->isInside(e))
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
	float boundary = enemies[0].size() * 2;

	for (int i = 0; i < enemies.size(); i++){
		for (int j = 0; j < enemies[i].size(); j++)
		{
			if (enemies[i][j] == 1)
			{
				entities.push_back(new Enemy(rand() % Enemy::enemies.size(), i, true, i * (maxVel / enemies.size()),  j * 2, boundary));
			}
			else if (enemies[i][j] == 2) {
				entities.push_back(new Enemy(rand() % Enemy::enemies.size(), i, false, i * (maxVel / enemies.size()), j * 2, boundary));
			}
		}
	}
}

void LevelState::showFog() {
	float fogColor[4] = { 0.7, 0.7, 0.7 };

	glEnable(GL_FOG);
	if (Game::inst().getCamara()->state == Game::inst().getCamara()->ISOMETRIC) {
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_START, 23.f);
		glFogf(GL_FOG_END, 28.f);
		glFogf(GL_FOG_DENSITY, 1.f);
	}
	else {
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_START, 15.f);
		glFogf(GL_FOG_END, 20.f);
		glFogf(GL_FOG_DENSITY, 1.f);
	}
}