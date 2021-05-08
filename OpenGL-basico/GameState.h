#pragma once
#include "SDL.h"
#include "SDL_opengl.h"

#include <map>

using namespace std;
class GameState
{
	public:
		GameState();
		virtual void init();
		virtual void update();
		virtual void render();
		virtual void destroy();
};

