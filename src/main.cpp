#include "SDL2/SDL.h"
#include <iostream>

using namespace std;

int width = 700;
int height = 700;

SDL_Window *window;
SDL_Renderer *renderer;

void scene_clear() {
  SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
  SDL_RenderClear(renderer);
}

void setup() {

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    cout << "SDL cannot init" << endl;

  window = SDL_CreateWindow("sdl_mandelbrot", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, width, height,
                            SDL_WINDOW_OPENGL);
  if (window == nullptr)
    cout << "Window cannot be created" << endl;

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (renderer == nullptr)
    cout << "Renderer cannot init" << endl;
}

int main(int argc, char *argv[]) {
  setup();

  scene_clear();
  double x, y, x0, y0, xtemp;

  int iteration, max_iterations = 1000;

  double brightness;

  for (int px = 0; px < width; px++) {
    for (int py = 0; py < height; py++) {
      iteration = 0;
      x0 = (double)px / (width / 4) - 2.0;
      y0 = (double)py / (height / 4) - 2.0;
      x = 0;
      y = 0;
      while (((x * x + y * y) <= 4) && iteration < max_iterations) {
        xtemp = x * x - y * y + x0;
        y = 2 * x * y + y0;
        x = xtemp;
        iteration++;
      }

      brightness = 255.0 * (double)iteration / 50;

      SDL_SetRenderDrawColor(renderer, (int)brightness, (int)brightness,
                             (int)brightness, 255);
      SDL_RenderDrawPoint(renderer, px, py);
    }
  }
  SDL_RenderPresent(renderer);

  bool mainLoop = true;
  SDL_Event event;
  while (mainLoop) {
    // scene_clear();

    // SDL_RenderPresent(renderer);

    if (SDL_PollEvent(&event)) {

      switch (event.type) {
      case SDL_QUIT:
        mainLoop = false;
        break;
      }
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
