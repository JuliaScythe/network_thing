#pragma once

#include "../Node.hpp"
#include <optional>

struct RoutingTableEntry {
  Node *dest;
  Node *route;
};

class NodeSwitch : public Node {
public:
  NodeSwitch(int x, int y, int sizeX, int sizeY, int r, int g, int b, int a);
  void forwardPacket(Packet &p, Connection *c) override;
private:
  std::optional<Node *> findRouteToNode(Node *n);
  std::vector<RoutingTableEntry> mRoutingTable;
};

// vim: sw=2 et
