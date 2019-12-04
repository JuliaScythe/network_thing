#include "Hub.hpp"

void NodeHub::forwardPacket(Packet &p) {
  Packet pNew = p;
  pNew.mHopLimit--;
  for (Connection *c : connections) {
    if (c->nodeSrc.lock().get() == this) {
      c->sendPacket(pNew, this);
    }
  }
}

// vim: sw=2 et
