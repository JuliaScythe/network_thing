#pragma once

#include <SDL2/SDL.h>

class Display {
public:
  Display(const char *title, int width, int height);
  ~Display();
  void update();
  SDL_Renderer *m_renderer;
  SDL_GLContext m_gl;
  void circle(unsigned x, unsigned y, unsigned radius);
  void filledCircle(unsigned x, unsigned y, unsigned radius);
private:
  SDL_Window *m_window;
};

// vim: et sw=2
