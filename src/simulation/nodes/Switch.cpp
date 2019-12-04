#include "Switch.hpp"

#include <optional>

std::optional<Node *> NodeSwitch::findRouteToNode(Node *n) {
  for (RoutingTableEntry &e : mRoutingTable) {
    if (e.dest == n) return std::optional<Node *>(e.route);
  }

  // TODO: ARP

  return std::nullopt;
}

void NodeSwitch::forwardPacket(Packet &p, Connection *c) {
  std::optional<Node *> nextHop = findRouteToNode(p.mDst.lock().get());
  if (!nextHop) return;

  Packet pNew = p;
  pNew.mHopLimit--;

  for (Connection *c : connections) {
    if (c->isDst(*nextHop)) {
      c->sendPacket(pNew, this);
      break;
    }
  }
}

// vim: sw=2 et
