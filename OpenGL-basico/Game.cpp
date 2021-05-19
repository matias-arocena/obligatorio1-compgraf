#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include "GameState.h"
#include "LevelState.h"
#include "Game.h"
#include "Camara.h"
#include <GL/freeglut.h>

using namespace std;

Uint32 timer(Uint32 interval, void* param) {
	Game::inst().seconds++;
	return(interval);
}

int main(int argc, char* argv[]) 
{
	//INICIALIZACION
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("Not Crossy Road",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);

	glutInit(&argc, argv);

	SDL_SetWindowGrab(win, SDL_TRUE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	glMatrixMode(GL_PROJECTION);

	float color = 0;
	glClearColor(color, color, color, 1);

	gluPerspective(45, 640 / 480.f, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	
	Game::inst().setState(new LevelState());

	//---------------------
	float x, y, z;

	x = 3;
	y = 7;
	z = 7;
	float degrees = 0;

	bool rotate = false;
	GLfloat ambientLight[4] = { 0.1, 0.1, 0.1, 0.1 };
	//FIN INICIALIZACION
	bool textOn = true;

	SDL_Event evento;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;

	SDL_AddTimer(1000, timer, 0);

	//LOOP PRINCIPAL
	do 
	{

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		Game::inst().deltaTime = Game::inst().gameVelocity * (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

		Game::inst().checkEvents();

		if (Game::inst().stateChanged)
		{
			Game::inst().stateChanged = false;
			continue;
		}

		Game::inst()._state->update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glLoadIdentity();
		glEnable(GL_NORMALIZE);
		

		Game::inst().cam->update();
		if(!Game::inst().lightChanged)
			Game::inst().luz_posicion[2] = Game::inst().getCamara()->getPos().z;
		
		//PRENDO LA LUZ (SIEMPRE DESPUES DEL gluLookAt)
		glEnable(GL_LIGHT0); // habilita la luz 0
		glLightfv(GL_LIGHT0, GL_POSITION, Game::inst().luz_posicion);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Game::inst().diffuseLight);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
				
		//glPushMatrix();
		
		//DIBUJAR OBJETOS
		
		Game::inst()._state->render();
		//drawHUD();
		
		//FIN DIBUJAR OBJETOS


		SDL_GL_SwapWindow(win);

	} while (!Game::inst()._fin);
	//FIN LOOP PRINCIPAL

	// LIMPIEZA
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

void Game::setState(GameState *aGameState)
{
	if (_state)
	{
		cout << "destroy state" << endl;
		_state->destroy();
		delete _state;
	}
	_state = aGameState;
	_state->init();
	stateChanged = true;
}

void Game::checkEvents()
{
	//MANEJO DE EVENTOS
	SDL_Event evento;
	while (SDL_PollEvent(&evento))
	{
		switch (evento.type)
		{
		case SDL_KEYDOWN:
			// cout << "Key Down" << endl;
			switch (evento.key.keysym.sym)
			{
			case SDLK_q:
				_fin = true;
				break;
			case SDLK_PERIOD:
				if(gameVelocity < 3)
					gameVelocity += 0.1f;
				break;
			case SDLK_COMMA:
				if(gameVelocity > 0.1f) 
					gameVelocity -= 0.1f;
				break;
			case SDLK_0:
				gameVelocity = 1.0f;
				break;
			case SDLK_1:
				lightChanged = true;
				luz_posicion[0] -= 1;
				break;
			case SDLK_2:
				lightChanged = true;
				luz_posicion[0] += 1;
				break;
			case SDLK_3:
				lightChanged = true;
				luz_posicion[1] -= 1;
				break;
			case SDLK_4:
				lightChanged = true;
				luz_posicion[1] += 1;
				break;
			case SDLK_5:
				lightChanged = true;
				luz_posicion[2] -= 1;
				break;
			case SDLK_6:
				lightChanged = true;
				luz_posicion[2] += 1;
				break;
			case SDLK_7:
				diffuseLight[0] = fmod(diffuseLight[0] + 0.1, 1);
				break;
			case SDLK_8:
				diffuseLight[1] = fmod(diffuseLight[1] + 0.1, 1);
				break;
			case SDLK_9:
				diffuseLight[2] = fmod(diffuseLight[2] + 0.1, 1);
				break;
			}

			break;
		}

		Game::inst()._state->onEvent(evento);
		Game::inst().cam->onEvent(evento);
	}
	//FIN MANEJO DE EVENTOS
};

Camara * Game::getCamara() {
	return cam;
}
