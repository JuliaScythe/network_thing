#include "Connection.hpp"
#include <memory>


Connection::Connection(std::weak_ptr<Node> nodeA, std::weak_ptr<Node> nodeB) : nodeA(nodeA), nodeB(nodeB) {}

void Connection::DoTick() {
  return;
}

void Connection::sendPacket(Packet &packet, Node *node) {
  mPackets.push_back(packet);
  
}
