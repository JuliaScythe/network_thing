#include "Node.hpp"
#include "../graphics/Display.hpp"

Node::Node(int x, int y, int sizeX, int sizeY) 
  : x(x), y(y), sizeX(sizeX), sizeY(sizeY) {}

SDL_Texture *Node::m_texture = nullptr;

void Node::doRender() {
  if (!Node::m_texture) {
    Node::m_texture = Display::inst->createTexture("./res/node_basic.svg");
  }

  SDL_Rect dst = {.x=x, .y=y, .w=sizeX, .h=sizeY};
  SDL_RenderCopy(Display::inst->m_renderer, Node::m_texture, NULL, &dst);
}

void Node::addConnection(Connection connection) {
  connections.push_back(connection);
}

std::vector<Connection> Node::getConnections() {
  return connections;
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

void Node::handlePacket(Packet &p) {}
void Node::forwardPacket(Packet &p) {}

// vim: sw=2 et
