#include "Display.hpp"
#include "../simulation/Simulation.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <cmath>

Display::Display(const char *title, int width, int height) {
  Display::inst = this;

  if (SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(SDL_GetError());
  }

  m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

  if (!m_window) {
    throw std::runtime_error(SDL_GetError());
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

}

void Display::mainLoop() {
  Simulation sim;
  bool running = true;
  bool x = false;
  while (running) {
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    for (auto &obj : sim.objects) {
      obj->doRender();
    }

    update();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }
  }
}

SDL_Texture *Display::createTexture(const char *path) {
  SDL_RWops *rwops = SDL_RWFromFile(path, "r");
  if (!rwops) {
    throw std::runtime_error(SDL_GetError());
  }

  SDL_Surface *img = IMG_LoadSVG_RW(rwops);
  if (!img) {
    throw std::runtime_error(IMG_GetError());
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, img);
  if (!texture) {
    throw std::runtime_error(SDL_GetError());
  }

  return texture;
}

void Display::update() {
  SDL_RenderPresent(m_renderer);
}

Display::~Display() {
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

// vim: sw=2 et
