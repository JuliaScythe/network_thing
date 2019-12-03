#include "Node.hpp"

Node::Node(int x, int y, int sizeX, int sizeY, int r, int g, int b, int a) 
  : x(x), y(y), sizeX(sizeX), sizeY(sizeY), r(r), g(g), b(b), a(a) {}


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
