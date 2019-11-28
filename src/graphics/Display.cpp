#include "Display.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <cmath>

#define TAU 6.28318

Display::Display(const char *title, int width, int height) {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(SDL_GetError());
  }

  m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

  if (!m_window) {
    throw std::runtime_error(SDL_GetError());
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
  SDL_RenderClear(m_renderer);

  // Test
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
  SDL_RWops *x = SDL_RWFromFile("./res/node_basic.svg", "r");
  SDL_Surface *img = IMG_LoadSVG_RW(x);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, img);

  SDL_Rect dst = {.x=100, .y=100, .w=200, .h=200};

  SDL_RenderCopy(m_renderer, texture, NULL, &dst);

  update();

  SDL_Delay(2000);
}

void Display::update() {
  SDL_RenderPresent(m_renderer);
}

Display::~Display() {
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

// vim: sw=2 et
