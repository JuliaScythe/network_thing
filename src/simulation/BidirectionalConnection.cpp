#include "BidirectionalConnection.hpp"

void BidirectionalConnection::sendPacket(Packet &packet, Node *node) {
  if (node == nodeSrc.lock().get()) {
    mPackets.push_back(packet);
  } else if (node == nodeDst.lock().get()) {
    mReversePackets.push_back(packet);
  } else {
	throw new std::runtime_error("Invalid source node!");
  }
}
