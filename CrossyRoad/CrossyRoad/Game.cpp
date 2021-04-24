#include "Game.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "gl/GLU.h"

Game::Game(int width, int height) {
	running = true;

	glMatrixMode(GL_PROJECTION);
	glClearColor(0, 0, 0, 1);
	gluPerspective(45, width / height, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
}

void Game::GameLoop(float deltaTime) {
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            running = false;
            break;
        default:
            break;
        }
    }
}

bool Game::isRunning()
{
	return running;
}
