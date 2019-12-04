#pragma once

#include "../Node.hpp"

class NodeHub : public Node {
public:
  using Node::Node;
  virtual void forwardPacket(Packet &p, Connection *c) override;
  virtual void doRender() override;
  virtual int sizeY() override;
};

// vim: sw=2 et
