#pragma once

#include <SDL2/SDL.h>
#include "../locking_ptr.hpp"
#include "../simulation/Simulation.hpp"

class Display {
public:
  Display(const char *title, int width, int height);
  ~Display();
  void update();
  void mainLoop();
  void doTick();
  SDL_Renderer *m_renderer;
  SDL_GLContext m_gl;
  SDL_Texture *createTexture(const char *path);

  bool m_close = false;

  static Display *inst;
private:
  SDL_Window *m_window;
  locking_ptr<Simulation> m_sim;
};

// vim: et sw=2
