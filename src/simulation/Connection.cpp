#include "Connection.hpp"
#include <memory>

PacketTransfer::PacketTransfer(Packet &p)
  : packet(p), progress(0.0f) {}

Connection::Connection(std::weak_ptr<Node> nodeSrc, std::weak_ptr<Node> nodeDst) : nodeSrc(nodeSrc), nodeDst(nodeDst) {}

void Connection::DoTick() {
  return;
}

void Connection::sendPacket(Packet &packet, Node *node) {
  if (node != nodeSrc) {
      
  }

  mPackets.push_back({packet});
}

// vim: sw=2 et
