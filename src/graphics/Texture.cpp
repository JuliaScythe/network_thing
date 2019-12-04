#include "Texture.hpp"
#include "Display.hpp"

Texture Texture::NODE("res/node_basic.svg");
Texture Texture::HUB("res/node_hub.svg");

Texture::Texture(const char *file) : m_file(file) {}

void Texture::init() {
  m_texture = Display::inst->createTexture(m_file);
  SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
}

void Texture::initAll() {
  NODE.init();
  HUB.init();
}

float Texture::ratio() {
  return (float)m_height / m_width;
}
