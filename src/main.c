#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <unistd.h>
#include "settings.h"

struct Player {
  char * texture_path;
  SDL_Surface* surface;
  SDL_Texture* texture;
  SDL_Rect rect;
  float rel_x;
  float rel_y;
  float vel_x;
  float vel_y;
  int abs_x;
  int abs_y;
  float rel_width;
  float rel_height;
  int abs_width;
  int abs_height;
};

void InitPlayer(struct Player* player, SDL_Renderer* renderer) {
  player->texture_path = "../assets/player.png";
  player->surface = IMG_Load(player->texture_path);
  player->texture = SDL_CreateTextureFromSurface(renderer, player->surface);
  SDL_FreeSurface(player->surface);
  player->rel_x = 0.1;
  player->rel_y = 0.1;
  player->vel_x = 0.01;
  player->vel_y = 0.01;
  player->rel_width = 0.2;
  // player->rel_height = 0.2;
  player->rel_height = (player->rel_width * player->surface->w/player->surface->h);
}

void UpdatePlayer(struct Player* player, SDL_Renderer* renderer, const Uint8* keys, SDL_Event event) {

  player->abs_x = round(player->rel_x * WIN_WIDTH);
  player->abs_y = round(player->rel_y * WIN_HEIGHT);
  player->abs_width = round(player->rel_width * WIN_WIDTH);
  player->abs_height = round(player->rel_height * WIN_HEIGHT);
  player->rect = (SDL_Rect){ .x = player->abs_x, .y = player->abs_y,
                             .w = player->abs_width, .h = player->abs_height};
  SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_KEYDOWN) {
      printf("pressed\n");
      // if (event.key.keysym.sym == SDLK_w) { player.rel_y -= player.vel_y; };
      // if (event.key.keysym.sym == SDLK_a) { player.rel_x -= player.vel_x; };
      // if (event.key.keysym.sym == SDLK_s) { player.rel_y += player.vel_y; };
      // if (event.key.keysym.sym == SDLK_d) { player.rel_x += player.vel_x; };
      if (keys[SDL_SCANCODE_W]) { player->rel_y -= player->vel_y; };
      if (keys[SDL_SCANCODE_A]) { player->rel_x -= player->vel_x; };
      if (keys[SDL_SCANCODE_S]) { player->rel_y += player->vel_y; };
      if (keys[SDL_SCANCODE_D]) { player->rel_x += player->vel_x; };
    }
  }

};

int main(int argc, char* argv[]) {

  SDL_Init(SDL_INIT_VIDEO);                               // Initialize SDL
  const Uint8* keys = SDL_GetKeyboardState(NULL);
  SDL_Window* window = SDL_CreateWindow("game",           // Create a window
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WIN_WIDTH, WIN_HEIGHT,
                                        SDL_WINDOW_RESIZABLE);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, // Create a renderer
                                              SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

  struct Player player;
  struct Player player2;
  InitPlayer(&player, renderer);


  typedef enum {
    state_menu,
    state_gameplay,
    state_paused,
  } State;

  SDL_Event event;
  bool running = true;

  // Game loop
  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }
       
    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
       
    // Update the renderer
    UpdatePlayer(&player, renderer, keys, event);
    SDL_RenderPresent(renderer);
    // sleep(1/120);
   }
   
  // Clean up and exit
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
  }
}
