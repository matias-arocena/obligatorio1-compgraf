#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "FreeImage.h"
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>

#include "MovementTestState.h"
#include "Player.h"

	MovementTestState::MovementTestState()
	{
	}

	void MovementTestState::init()
	{
		player = new Player();
	}

	void MovementTestState::update()
	{
		//cout << "update" << endl;
		
		player->update();

		//MANEJO DE EVENTOS
		SDL_Event evento;
		while (SDL_PollEvent(&evento)) 
		{
			//cout << "polling event" << endl;
		}
		//FIN MANEJO DE EVENTOS
	}

	void MovementTestState::render()
	{
		player->render();
	}

	void MovementTestState::destroy()
	{
		player->destroy();
	}

