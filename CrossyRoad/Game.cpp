#include "Game.h"
#include "gl/GLU.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <string>

const bool FLIP_NORMALS = true;

Game::Game(int width, int height) {
	running = true;
    lighting = true;

	glMatrixMode(GL_PROJECTION);
	glClearColor(0, 0, 0, 1);
	gluPerspective(45, width / height, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
        
    Model* cube = new Model();
    cube->LoadMesh("../assets/cube/cube.obj");
    models["cube"] = cube;

    Model* tree = new Model(FLIP_NORMALS);
    tree->LoadMesh("../assets/tree.3ds");
    models["tree"] = tree;
    
    

    lightPosition = { 0.5, 1, 6, 1 };
    ambientLightColor = { 0.3, 0.3, 0.3, 1 };
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
            break;
        case SDLK_r:
            models["tree"]->Rotate(5 * deltaTime);
            break;
        case SDLK_l:
            lighting = !lighting;
            break;
        default:
            break;
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);
    glLoadIdentity();
    gluLookAt(0, 0, 15, 0, 0, 0, 0, 1, 0);
    glEnable(GL_DEPTH_TEST); 
    
    if (onlyWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glPushMatrix();
    if (lighting) {
        glEnable(GL_LIGHTING);
    }
    models["cube"]->Render();
    if (lighting) {
        glDisable(GL_LIGHTING);
    }
    glPopMatrix();

    glTranslated(6, 0, 0);
    glPushMatrix();
    if (lighting) {
        glEnable(GL_LIGHTING);
    }
    models["tree"]->Render();
    if (lighting) {
        glDisable(GL_LIGHTING);
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
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

}

bool Game::isRunning()
{
	return running;
}
