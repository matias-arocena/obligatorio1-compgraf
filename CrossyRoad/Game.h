#pragma once
class Game {
	bool running;
public:
	Game() :Game(640, 480){};
	Game(int width, int height);
	void GameLoop(float deltaTime);
	bool isRunning();
};

