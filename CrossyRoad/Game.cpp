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
        
    Model* model = new Model();
    model->LoadMesh("../assets/tree.3ds");
    models["tree"] = model;

    lightPosition = { 0, 1, -1, 1 };
    ambientLightColor = { 0.7, 0.7, 0.7, 1 };
    diffuseLightColor = { 1, 1, 1, 1 };
}

void Game::GameLoop(double deltaTime) {
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
            running = false;
            break;
        case SDLK_w:
            onlyWireframe = !onlyWireframe;
            for (auto& kv: models) {
                kv.second->ShowOnlyWireframe(onlyWireframe);
            }
            break;
        default:
            break;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    glTranslatef(0, 1, -1);
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex3d(-0.3, -0.3, 0);
    glVertex3d(0.3, -0.3, 0);
    glVertex3d(0.3, 0.3, 0);
    glVertex3d(-0.3, 0.3, 0);
    glEnd();

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition.data());
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightColor.data());
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLightColor.data());
    glPopMatrix();

    models["tree"]->Rotate(.1 * deltaTime);
    glEnable(GL_LIGHTING);
    models["tree"]->Render();
    glDisable(GL_LIGHTING);
}

bool Game::isRunning()
{
	return running;
}
