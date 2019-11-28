#include "Hub.hpp"

void NodeHub::forwardPacket(Packet &p) {
  Packet pNew = p;
  pNew.mHopLimit--;
  for (Connection &c : connections) {
    c.sendPacket(pNew, this);
  }
}

// vim: sw=2 et
