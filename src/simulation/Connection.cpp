#include "Connection.hpp"
#include <memory>


Connection::Connection(std::weak_ptr<Node> nodeA, std::weak_ptr<Node> nodeB) : nodeA(nodeA), nodeB(nodeB) {}

void Connection::DoTick() {
  return;
}
