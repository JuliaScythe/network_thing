#include "Node.hpp"
#include "../graphics/Display.hpp"

Node::Node(int x, int y, int width)
  : mX(x), mY(y), m_width(width) {}

SDL_Texture *Node::s_texture = nullptr;
int Node::s_txt_width = 0;
int Node::s_txt_height = 0;

void Node::doRender() {
  if (!Node::s_texture) {
    Node::s_texture = Display::inst->createTexture("./res/node_basic.svg");
    SDL_QueryTexture(Node::s_texture, nullptr, nullptr, &Node::s_txt_width, &Node::s_txt_height);
  }

  SDL_Rect dst = {.x=mX, .y=mY, .w=sizeX(), .h=sizeY()};
  SDL_RenderCopy(Display::inst->m_renderer, Node::s_texture, NULL, &dst);
}

void Node::doTick() {
  return;
}

void Node::receivePacket(Packet &p) {
  if (p.mDst.lock().get() == this) {
    handlePacket(p);
  }
  forwardPacket(p);
}

int Node::sizeX() {
  return m_width;
}

int Node::sizeY() {
  return m_width * s_txt_height / s_txt_width;
}

void Node::handlePacket(Packet &p) {}
void Node::forwardPacket(Packet &p) {}

// vim: sw=2 et
