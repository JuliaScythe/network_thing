#include "Texture.hpp"
#include "Display.hpp"

Texture Texture::NODE("res/node_basic.svg");
Texture Texture::HUB("res/node_hub.svg");

Texture Texture::PACKET("res/packet_basic.svg");
Texture Texture::PACKET_ERROR("res/packet_error.svg");

Texture Texture::EXPLOSION("res/boom.svg");

Texture::Texture(const char *file) : m_file(file) {}

void Texture::init() {
  m_texture = Display::inst->createTexture(m_file);
  SDL_QueryTexture(m_texture, nullptr, nullptr, &m_width, &m_height);
}

void Texture::initAll() {
  NODE.init();
  HUB.init();  // This is a really shitty way of keeping track of textures, cant this just be called in the constructor?
  EXPLOSION.init();

  PACKET.init();
  PACKET_ERROR.init();
}

float Texture::ratio() {
  return (float)m_height / m_width;
}
