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

void BidirectionalConnection::doTick() {
  Connection::doTick(); // Ensure the forward packets are moved forward

  // Move the reverse packets forward
  for (unsigned i = 0; i < mReversePackets.size(); i++) {
    mReversePackets[i].progress += deltaProgress;
    if (mReversePackets[i].progress > 1.0f) {
      auto x = mReversePackets.begin() + (i--);
      mReversePackets.erase(x);
    }
  

}
