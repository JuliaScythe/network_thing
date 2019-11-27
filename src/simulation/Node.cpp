#include "Node.hpp"

Node::Node(int x, int y, int sizeX, int sizeY, int r, int g, int b, int a) 
  : x(x), y(y), sizeX(sizeX), sizeY(sizeY), r(r), g(g), b(b), a(a) {}


void Node::addConnection(Connection connection) {
  connections.push_back(connection);
}

std::vector<Connection> Node::getConnections() {
  return connections;
}

void Node::DoTick() {
  return;
}
// vim: et sw=2
