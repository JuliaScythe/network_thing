#pragma once

#include <SDL2/SDL.h>

class Display {
public:
  Display(const char *title, int width, int height);
  ~Display();
  void update();
  void mainLoop();
  SDL_Renderer *m_renderer;
  SDL_GLContext m_gl;
  SDL_Texture *createTexture(const char *path);
private:
  SDL_Window *m_window;
};

// vim: et sw=2
