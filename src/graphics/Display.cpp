#include "Display.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>

SDL_Surface *Display::m_surface;
SDL_Window *Display::m_window;

void Display::init(const char *title, int width, int height) {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(SDL_GetError());
  }

  m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

  if (!m_window) {
    throw std::runtime_error(SDL_GetError());
  }

  m_surface = SDL_GetWindowSurface(m_window);

  // Test
  SDL_FillRect(m_surface, NULL, 0xFFFFFF);
  update();
  SDL_Delay(2000);
}

void Display::update() {
  SDL_UpdateWindowSurface(m_window);
}

// vim: et sw=2
