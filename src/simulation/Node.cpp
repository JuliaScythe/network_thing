#include "Node.hpp"
#include "../graphics/Texture.hpp"
#include "../graphics/Display.hpp"

Node::Node(int x, int y, int width)
  : mX(x), mY(y), m_width(width) {}

void Node::doRender() {
  SDL_Rect dst = {.x=mX - sizeX() / 2, .y=mY - sizeY() / 2, .w=sizeX(), .h=sizeY()};
  SDL_RenderCopy(Display::inst->m_renderer, Texture::NODE.m_texture, NULL, &dst);

  if (mTickRenderTime >= std::chrono::system_clock::now()) {
    SDL_Rect tick = {.x=mX - 40, .y=mY - 45, .w=80, .h=85};
    SDL_RenderCopy(Display::inst->m_renderer, Texture::TICK.m_texture, NULL, &tick);
  }
}

void Node::doTick() {
  return;
}

void Node::receivePacket(Packet &p, Connection *c) {
  if (p.mDst.lock().get() == this) {
    handlePacket(p, c);
  }
  if (p.mHopLimit > 0) {
    forwardPacket(p, c);
  }
}

int Node::sizeX() {
  return m_width;
}

int Node::sizeY() {
  return m_width * Texture::NODE.ratio();
}

void Node::handlePacket(Packet &p, Connection *c) {
  mTickRenderTime = std::chrono::system_clock::now() + std::chrono::duration<int64_t, std::ratio<1, 2>>{1};
}

void Node::forwardPacket(Packet &p, Connection *c) {}

// vim: sw=2 et
