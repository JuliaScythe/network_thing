#pragma once

#include "Connection.hpp"

class BidirectionalConnection : public Connection {
public:
  std::vector<PacketTransfer> mReversePackets;
  void sendPacket(Packet &packet, Node *node);
};

// vim: sw=2 et
