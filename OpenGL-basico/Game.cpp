#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include "GameState.h"
#include "LevelState.h"
//#include "MovementTestState.h"
#include "Game.h"
#include "Camara.h"

using namespace std;



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

	glMatrixMode(GL_PROJECTION);

	float color = 0;
	glClearColor(color, color, color, 1);

	gluPerspective(45, 640 / 480.f, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	
	cout << "post create game" << endl;
	Game::inst().setState(new LevelState());

	cout << "pre begin loop";

	//---------------------
	float x, y, z;

	x = 3;
	y = 7;
	z = 7;
	float degrees = 0;

	bool rotate = false;
	GLfloat luz_posicion[4] = { -30, 15, 0, 1 };
	GLfloat diffuseLight[4] = { 1, 1, 1, 1 };
	GLfloat ambientLight[4] = { 0.1, 0.1, 0.1, 0.1 };
	//FIN INICIALIZACION
	bool textOn = true;

	SDL_Event evento;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;

	//LOOP PRINCIPAL
	do 
	{
		Game::inst().checkEvents();

		Game::inst()._state->update();
		
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		Game::inst().deltaTime = Game::inst().gameVelocity * (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glLoadIdentity();
		glEnable(GL_NORMALIZE);
		

		Game::inst().cam->update();
		luz_posicion[2] = Game::inst().getCamara()->getPos().z;
		//PRENDO LA LUZ (SIEMPRE DESPUES DEL gluLookAt)
		glEnable(GL_LIGHT0); // habilita la luz 0
		glLightfv(GL_LIGHT0, GL_POSITION, luz_posicion);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
				
		//glPushMatrix();
		
		//DIBUJAR OBJETOS
		
		Game::inst()._state->render();
		
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
	if (_state != NULL)
		_state->destroy();
	_state = aGameState;
	_state->init();
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
				gameVelocity += 0.1f;
				break;
			case SDLK_COMMA:
				if(gameVelocity > 0.1f) 
					gameVelocity -= 0.2f;
				break;
			case SDLK_0:
				gameVelocity = 1.0f;
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
