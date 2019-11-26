#include "Display.hpp"
#include <SDL2/SDL.h>

void Display::init() {
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
}
