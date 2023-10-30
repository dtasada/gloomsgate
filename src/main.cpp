#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>

#include "../include/RenderWindow.hpp"

int main(int argc, char* argv[]) {
	RenderWindow window = RenderWindow("Gloomsgate", 1280, 720);
	bool game_running = true;
	SDL_Texture* grass_texture = IMG_LoadTexture(window.renderer, "assets/grass-1.png");

	SDL_Event event;

	while (game_running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				game_running = false;
		}
		SDL_RenderClear(window.renderer);
		// SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
		SDL_RenderCopy(window.renderer, grass_texture, NULL, NULL);
		SDL_RenderPresent(window.renderer);
	}

	SDL_DestroyRenderer(window.renderer);
	SDL_Quit();

	return 0;
}
