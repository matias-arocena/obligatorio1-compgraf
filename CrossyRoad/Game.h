#pragma once
#include <map>
#include <string>
#include "Model.h"
class Game {
	bool running, onlyWireframe;
	std::map<std::string, Model*> models;
public:
	Game() :Game(640, 480){};
	Game(int width, int height);
	void GameLoop(double deltaTime);
	bool isRunning();
};

