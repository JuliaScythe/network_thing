#include "Switch.hpp"

#include <optional>

std::optional<Node *> NodeSwitch::findRouteToNode(Node *n) {
  for (RoutingTableEntry &e : mRoutingTable) {
    if (e.dest == n) return std::optional<Node *>(e.route);
  }

  // TODO: ARP

  return std::nullopt;
}

void NodeSwitch::forwardPacket(Packet &p) {
  std::optional<Node *> nextHop = findRouteToNode(p.mDst);
  if (!nextHop) return;

  Packet pNew = p;
  pNew.mHopLimit--;

  for (Connection &c : connections) {
    if (c.nodeA.lock().get() == nextHop ||
        c.nodeB.lock().get() == nextHop) {
      c.sendPacket(pNew, this);
      break;
    }
  }
}

// vim: sw=2 et
