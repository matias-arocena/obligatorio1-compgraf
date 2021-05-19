#include "LevelState.h"

#include "Enemy.h"

#include <iostream>
#include <sstream>
#include <GL/freeglut.h>
#include <fstream>
#include "Game.h"


void printWithFG(char* imprimible, int pos_hor, int pos_ver, bool size_big, int color) {
	switch (color) {
	case 1: //black
		glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
		break;
	case 2: //
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	}
	glRasterPos2i(pos_hor, pos_ver);
	char print_string[1000];
	sprintf_s(print_string, imprimible);
	const unsigned char* settings = reinterpret_cast<const unsigned char*>(print_string);
	if (size_big) {
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, settings);
	}
	else {
		glutBitmapString(GLUT_BITMAP_HELVETICA_12, settings);
	}
}

void dibuHUD(int score, int seconds) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, 640, 1.0, 480);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();

	char score_string[1000];
	sprintf_s(score_string, "%s%d", "Puntaje: ", score);
	printWithFG(score_string, 25, 450, true, 2);

	char time_string[1000];
	sprintf_s(time_string, "%s%d", "Tiempo: ", seconds);
	printWithFG(time_string, 25, 430, true, 2);

	printWithFG("Settings: ", 25, 150, false, 1);
	printWithFG("Pausa -> p", 25, 140, false, 1);
	printWithFG("Salir -> q", 25, 130, false, 1);
	printWithFG("Toggle wireframe -> w", 25, 120, false, 1);
	printWithFG("Toggle luz -> l", 25, 110, false, 1);
	printWithFG("Toggle textura -> t", 25, 100, false, 1);
	printWithFG("Toggle hitbox -> h", 25, 90, false, 1);
	printWithFG("Toggle interpolado - facetado -> f", 25, 80, false, 1);
	printWithFG("Aumento de velocidad -> .", 25, 70, false, 1);
	printWithFG("Disminucion de velocidad -> ,", 25, 60, false, 1);
	printWithFG("Movimiento de luz en x -> 1 Disminuye, 2 Aumenta", 25, 50, false, 1);
	printWithFG("Movimiento de luz en y -> 3 Disminuye, 4 Aumenta", 25, 40, false, 1);
	printWithFG("Movimiento de luz en z -> 5 Disminuye, 6 Aumenta", 25, 30, false, 1);
	printWithFG("Cambio de componente rojo en luz -> 7", 25, 20, false, 1);
	printWithFG("Cambio de componente verde en luz -> 8", 25, 10, false, 1);
	printWithFG("Cambio de componente azul en luz -> 9", 25, 0, false, 1);

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
	cout << "initLevelState" << endl;
	skybox = new Skybox(10, this);

	loadLevel(loadLevelFile(level));
	spawnEnemies(loadSpawnFile(level));

	player = new Player();
	player->setLevelState(this);
	player->setTileMap(tileMap);


	Game::inst().cam->setObjectToFollow(player);

	timeInitState = Game::inst().seconds;
}

void LevelState::onEvent(SDL_Event aEvent)
{
	player->onEvent(aEvent);
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
				case SDLK_f:
					flat = !flat;
					break;

				case SDLK_r:
					gameOver();
				default:
					break;
			}
			break;
		default:
			break;
	}

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
	
	skybox->update();

	player->calculateCollisions(entities);
	player->update();
}

void LevelState::render()
{
	dibuHUD(score, Game::inst().seconds - timeInitState);
	skybox->render();
	if (showLight) {
		glEnable(GL_LIGHTING);
		showFog();
		if (flat)
			glShadeModel(GL_FLAT);
		else
			glShadeModel(GL_SMOOTH);
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
				delete tileMap[j][i];
				tileMap[j][i] = NULL;
			}
		}
	}

	for (auto& e : entities) {
		e->destroy();
		delete e;
		e = NULL;
	}

	player->destroy();
	delete player;
	player = NULL;

	skybox->destroy();
	delete skybox;
	skybox = NULL;
}

Player* LevelState::getPlayer()
{
	return player;
}

void LevelState::gameOver()
{
	Game::inst().setState(new LevelState());
}

vector<vector<int>> LevelState::loadLevelFile(int level)
{
	std::vector<std::vector<int>> result;
	std::ifstream inputfile("../levels/tiles" + std::to_string(level) + ".txt");
	for (std::string line; getline(inputfile, line); )
	{
		std::vector<int> row;
		std::istringstream iss(line);
		std::string item;
		while (std::getline(iss, item, ' ')) {
			row.push_back(atoi(item.c_str()));
		}
		result.push_back(row);
	}
	return result;
}
vector<vector<int>> LevelState::loadSpawnFile(int level)
{
	std::vector<std::vector<int>> result;
	std::ifstream inputfile("../levels/spawn" + std::to_string(level) + ".txt");
	for (std::string line; getline(inputfile, line); )
	{
		std::vector<int> row;
		std::istringstream iss(line);
		std::string item;
		while (std::getline(iss, item, ' ')) {
			if (item == "R") {
				row.push_back(1);
			}
			else if (item == "L") {
				row.push_back(2);
			}
			else {
				row.push_back(atoi(item.c_str()));
			}
		}
		result.push_back(row);
	}
	return result;
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
	float maxVel = 15;
	float boundary = enemies[0].size() * 2;

	for (int i = 0; i < enemies.size(); i++)
	{
		// speed calculation
		float r = ((float)rand() / (RAND_MAX)) ; // random float between 0 and 1
		float velPerLine = (maxVel / enemies.size());
		float randomFactor = 10; //line margin of rand value i.e. for line 5, real value is between 5 * velPerLine to (5 + randomFactor) * velPerLine
		float vel = (i + (r * randomFactor)) * velPerLine;

		for (int j = 0; j < enemies[i].size(); j++)
		{
			if (enemies[i][j] == 1)
			{
				entities.push_back(new Enemy(rand() % Enemy::enemies.size(), i, true, vel,  j * 2, boundary));
			}
			else if (enemies[i][j] == 2) {
				entities.push_back(new Enemy(rand() % Enemy::enemies.size(), i, false, vel, j * 2, boundary));
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

void LevelState::checkScore()
{
	cout << "pog" << endl;
	int curPlayerZ = -player->getPos().z / Tile::TILE_WIDTH;
	if (curPlayerZ > maxPlayerZ)
	{
		score += 1;
		maxPlayerZ = curPlayerZ;

		cout << score << endl;
	}
}