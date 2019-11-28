#pragma once

#include "Connection.hpp"

class BidirectionalConnection : public Connection {
public:
  std::vector<PacketTransfer> mReversePackets;
};

// vim: sw=2 et
