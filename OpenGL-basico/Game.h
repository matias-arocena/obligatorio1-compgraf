#pragma once
#include "GameState.h"
#include "Camara.h"

class Game
{
	public:
		Camara* cam;
		static Game& inst()
		{
			static Game instance;
			return instance;
		}
		Game(Game const&) = delete;
		void operator=(Game const&) = delete;

		bool _fin = false;

		GameState* _state = NULL;
		void setState(GameState*);

		int seconds = 0;
		double deltaTime = 0;
		double getDeltaTime()
		{
			return deltaTime;
		}
		
		void checkEvents();

		Camara * getCamara();

		GLfloat luz_posicion[4] = { -30, 15, 0, 1 };
		GLfloat diffuseLight[4] = { 1, 1, 1, 1 };
		bool isPaused = false;
		bool lightChanged = false;
		float gameVelocity = 1.0f;
	private:

		Game() 
		{
			cam = new Camara();
		};
};
