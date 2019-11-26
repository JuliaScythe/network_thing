#include "Node.hpp"

Node::Node(std::vector<Connection> connections) : connections(connections) {
}


void Node::addConnection(Connection connection) {
  connections.push_back(connection);
}

std::vector<Connection> Node::getConnections() {
  return connections;
}
// vim: et sw=2
