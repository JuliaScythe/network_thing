#pragma once

#include "Connection.hpp"

class BidirectionalConnection : public Connection {
public:
  std::vector<std::shared_ptr<Packet>> mBackPackets;
  std::vector<int>> mBackPacketDistances
}
