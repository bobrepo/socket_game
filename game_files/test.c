
// file: sdl_window.c
#include <sdl.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  (void)argc;
  (void)argv;

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("SDL2 Window",          // window title
                                     SDL_WINDOWPOS_CENTERED, // x position
                                     SDL_WINDOWPOS_CENTERED, // y position
                                     800,                    // width
                                     600,                    // height
                                     SDL_WINDOW_SHOWN        // flags
  );

  if (!win) {
    fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *ren = SDL_CreateRenderer(
      win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!ren) {
    fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 1;
  }

  // main loop
  int running = 1;
  while (running) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        running = 0;
      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        running = 0;
    }

    // clear screen to a teal-ish color
    SDL_SetRenderDrawColor(ren, 30, 160, 150, 255); // r,g,b,a (0-255)
    SDL_RenderClear(ren);

    // present (swap buffers)
    SDL_RenderPresent(ren);
  }

  // cleanup
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
