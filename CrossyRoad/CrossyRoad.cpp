#include "Game.h"
#include <GL/glew.h> 
#include "gl/GLU.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <chrono>

int main(int argv, char** args) {
    SDL_Window* window = SDL_CreateWindow("Cross Road",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cerr << "[Video Error]:"
            << SDL_GetError()
            << std::endl;
        SDL_Quit();
        exit(1);
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (window == nullptr) {
        std::cerr << "[GL Context Error]:"
            << SDL_GetError()
            << std::endl;
    }

    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
    }

    Game *game = new Game();

    auto newTime = std::chrono::system_clock::now();
    while (game->isRunning()) {
        auto oldTime = newTime;
        newTime = std::chrono::system_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(newTime - oldTime).count();
           
        game->GameLoop(deltaTime);

        SDL_GL_SwapWindow(window);
    }

    delete game;

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}