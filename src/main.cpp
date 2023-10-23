#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <iostream>

#include "../include/RenderWindow.hpp"

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);
	SDL_Texture* grass_texture = window.loadTexture("assets/corbin.png");

	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning) {
		// Get our controls and events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}
		SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
		SDL_RenderClear(window.renderer);
		SDL_RenderPresent(window.renderer);
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}
