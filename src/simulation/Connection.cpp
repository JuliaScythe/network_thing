#include "Connection.hpp"
#include <memory>

PacketTransfer::PacketTransfer(Packet &p)
  : packet(p), progress(0.0f) {}

Connection::Connection(std::weak_ptr<Node> nodeA, std::weak_ptr<Node> nodeB) : nodeA(nodeA), nodeB(nodeB) {}

void Connection::DoTick() {
  return;
}

void Connection::sendPacket(Packet &packet, Node *node) {
  mPackets.push_back({packet});
}
