#pragma once

#include "Connection.hpp"

class BidirectionalConnection : public Connection {
public:
  using Connection::Connection;
  std::vector<PacketTransfer> mReversePackets;

  virtual void doTick() override;
  virtual void doRender() override;
  virtual void sendPacket(Packet &packet, Node *node) override;
  virtual bool isSrc(Node *n) override;
  virtual bool isDst(Node *n) override;
};

// vim: sw=2 et
