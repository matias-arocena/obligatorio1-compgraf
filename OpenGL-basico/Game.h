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

		bool isPaused = false;
		float gameVelocity = 1.0f;
		bool stateChanged = false;
	private:

		Game() 
		{
			cam = new Camara();
		};
};
