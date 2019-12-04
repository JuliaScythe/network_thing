#pragma once

#include <SDL2/SDL.h>

class Texture {
protected:
  Texture(const char *file);
  void init();
  const char *m_file;
public:
  SDL_Texture *m_texture;
  int m_width, m_height;
  float ratio();
  static Texture NODE;
  static Texture HUB;
  static Texture PACKET;
  static Texture PACKET_ERROR;
  static void initAll();
};
