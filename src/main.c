#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
	int width;
	int height;
	SDL_Window *window;
	SDL_Renderer *renderer;
} DisplayHandler;

typedef struct {
	bool running;
} GameHandler;

typedef struct {
	int x;
	int y;
} Player;

DisplayHandler DisplayHandlerInit(int width, int height, char title[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
	}

	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_BORDERLESS);
	if (!window) fprintf(stderr, "Error creating SDL Window.\n");

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, NULL);
	if (!renderer) fprintf(stderr, "Error creating SDL Renderer.\n");

	DisplayHandler val = {width, height, window, renderer};
	return val;
}

// Variables
DisplayHandler display;
GameHandler game;
Player player = {0, 0};

void PlayerUpdate(SDL_KeyCode key) {
	// switch (key) {
	// 	case SDLK_w:
	// 		player.y--;
	// 	break;
	// 	case SDLK_a:
	// 		player.x--;
	// 	break;
	// 	case SDLK_s:
	// 		player.y++;
	// 	break;
	// 	case SDLK_d:
	// 		player.x++;
	// 	break;
	// 	default:
	// 	break;
	// }

	if(key == SDLK_w) player.y--;
	if(key == SDLK_a) player.x--;
	if(key == SDLK_s) player.y++;
	if(key == SDLK_d) player.x++;

}

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			game.running = false;
		break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) game.running = false;
			PlayerUpdate(event.key.keysym.sym);
		break;
	}
}

void render() {
	SDL_SetRenderDrawColor(display.renderer, 0, 0, 0, 255);
	SDL_RenderClear(display.renderer);

	SDL_Rect rect = {player.x, player.y, 128, 128};
	SDL_SetRenderDrawColor(display.renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(display.renderer, &rect);

	SDL_RenderPresent(display.renderer);
}

int main() {
	display = DisplayHandlerInit(1280, 720, "Game");
	game.running = true;

	while (game.running) {
		process_input();
		render();
	}

	SDL_DestroyRenderer(display.renderer);
	SDL_DestroyWindow(display.window);
	SDL_Quit();

	return 0;
}
