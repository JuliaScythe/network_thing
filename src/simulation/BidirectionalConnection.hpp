#pragma once

#include "Connection.hpp"

class BidirectionalConnection : public Connection {
public:
  std::vector<PacketTransfer> mReversePackets;
};
