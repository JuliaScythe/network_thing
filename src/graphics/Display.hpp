#pragma once

#include <SDL2/SDL.h>

class Display {
public:
  static void init(const char *title, int width, int height);
  static void update();
  static SDL_Surface *m_surface;
private:
  static SDL_Window *m_window;
};

// vim: et sw=2
