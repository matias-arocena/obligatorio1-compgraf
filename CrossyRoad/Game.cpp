#include "Game.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "gl/GLU.h"
#include <string>

Game::Game(int width, int height) {
	running = true;

	glMatrixMode(GL_PROJECTION);
	glClearColor(0, 0, 0, 1);
	gluPerspective(45, width / height, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);
    
    Model* model = new Model();
    model->LoadMesh("../assets/pinchos.3ds");
    models["cube"] = model;
}

void Game::GameLoop(double deltaTime) {
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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);
    
    models["cube"]->Render();
}

bool Game::isRunning()
{
	return running;
}
