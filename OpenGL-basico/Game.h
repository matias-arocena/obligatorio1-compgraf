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

		double deltaTime = 0;
		double getDeltaTime()
		{
			return deltaTime;
		}
		
		void checkEvents();

		Camara * getCamara();

	private:
		Game() 
		{
			cam = new Camara();
		};
};
