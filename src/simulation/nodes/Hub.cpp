#include "Hub.hpp"
#include "../../graphics/Texture.hpp"
#include "../../graphics/Display.hpp"

void NodeHub::forwardPacket(Packet &p, Connection *in) {
  Packet pNew = p;
  pNew.mHopLimit--;
  for (Connection *c : connections) {
    if (c == in) continue;
    printf("enumerate conn\n");
    if (c->isSrc(this)) {
    printf("send on conn\n");
      c->sendPacket(pNew, this);
    }
  }
}

void NodeHub::doRender() {
  SDL_Rect dst = {.x=mX, .y=mY, .w=sizeX(), .h=sizeY()};
  SDL_RenderCopy(Display::inst->m_renderer, Texture::HUB.m_texture, NULL, &dst);
}

int NodeHub::sizeY() {
  return sizeX() * Texture::HUB.ratio();
}

// vim: sw=2 et
