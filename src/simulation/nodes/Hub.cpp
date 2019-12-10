#include "Hub.hpp"
#include "../../graphics/Texture.hpp"
#include "../../graphics/Display.hpp"

void NodeHub::forwardPacket(Packet &p, Connection *in) {
  Packet pNew = p;
  pNew.mHopLimit--;
  for (Connection *c : connections) {
    if (c == in) continue;
    if (c->isSrc(this)) {
      c->sendPacket(pNew, this);
    }
  }
}

void NodeHub::doRender() {
  SDL_Rect dst = {.x=mX - sizeX() / 2, .y=mY - sizeY() / 2, .w=sizeX(), .h=sizeY()};
  SDL_RenderCopy(Display::inst->m_renderer, Texture::HUB.m_texture, NULL, &dst);
}

int NodeHub::sizeY() {
  return sizeX() * Texture::HUB.ratio();
}

// vim: sw=2 et
