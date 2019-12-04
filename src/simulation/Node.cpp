#include "Node.hpp"
#include "../graphics/Texture.hpp"
#include "../graphics/Display.hpp"

Node::Node(int x, int y, int width)
  : mX(x), mY(y), m_width(width) {}

void Node::doRender() {
  SDL_Rect dst = {.x=mX, .y=mY, .w=sizeX(), .h=sizeY()};
  SDL_RenderCopy(Display::inst->m_renderer, Texture::NODE.m_texture, NULL, &dst);
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

void Node::handlePacket(Packet &p, Connection *c) {}
void Node::forwardPacket(Packet &p, Connection *c) {}

// vim: sw=2 et
