#include "Hub.hpp"
#include "../../graphics/Display.hpp"

SDL_Texture *NodeHub::s_texture = nullptr;
int NodeHub::s_txt_width = 0;
int NodeHub::s_txt_height = 0;

void NodeHub::forwardPacket(Packet &p) {
  Packet pNew = p;
  pNew.mHopLimit--;
  for (Connection *c : connections) {
    if (c->isSrc(this)) {
      c->sendPacket(pNew, this);
    }
  }
}

void NodeHub::doRender() {
  if (!NodeHub::s_texture) {
    NodeHub::s_texture = Display::inst->createTexture("./res/node_hub.svg");
    SDL_QueryTexture(NodeHub::s_texture, nullptr, nullptr, &NodeHub::s_txt_width, &NodeHub::s_txt_height);
  }

  SDL_Rect dst = {.x=mX, .y=mY, .w=sizeX(), .h=sizeY()};
  SDL_RenderCopy(Display::inst->m_renderer, NodeHub::s_texture, NULL, &dst);
}

// vim: sw=2 et
