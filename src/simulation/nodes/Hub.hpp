#pragma once

#include "../Node.hpp"

class NodeHub : public Node {
public:
  using Node::Node;
  void forwardPacket(Packet &p) override;
};

// vim: sw=2 et
