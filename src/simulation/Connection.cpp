#include "Connection.hpp"
#include <memory>
#include <vector>

PacketTransfer::PacketTransfer(Packet &p)
  : packet(p), progress(0.0f) {}

PacketTransfer &PacketTransfer::operator=(const PacketTransfer &other) {
  packet = other.packet;
  progress = other.progress;
  return *this;
}

Connection::Connection(std::weak_ptr<Node> nodeSrc, std::weak_ptr<Node> nodeDst, double deltaProgress) : nodeSrc(nodeSrc), nodeDst(nodeDst), deltaProgress(deltaProgress) {}

void Connection::DoTick() {
  for (unsigned i = 0; i < mPackets.size(); i++) {
    mPackets[i].progress += deltaProgress;
    if (mPackets[i].progress > 1.0f) {
      auto x = mPackets.begin() + (i--);
      mPackets.erase(x);
    }
  }
}

void Connection::sendPacket(Packet &packet, Node *node) {
  if (node != nodeSrc.lock().get()) {
    throw new std::runtime_error("Invalid source node!");
  }

  mPackets.push_back({packet});
}

// vim: sw=2 et
