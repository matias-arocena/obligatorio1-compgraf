#pragma once
#include "GameState.h"

class Game
{
	public:
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

	private:
		Game() 
		{
		};
};
