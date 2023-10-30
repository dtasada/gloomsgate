#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

// class RenderWindow {
// public:
// 	RenderWindow(const char* title, int width, int height);
// 	SDL_Texture* loadTexture(const char* file_path);
// 	void render(SDL_Texture* tex);
// 	SDL_Window* window;
// 	SDL_Renderer* renderer;
// // private:
// };

class RenderWindow {
public:
	// RenderWindow(const char* title, int width, int height) {};
	char* title = title;
	int width = width;
	int height = height;
	SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
};

void asdf() {
	NULL;
}
