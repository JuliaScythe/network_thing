#include "Connection.hpp"
#include <memory>
#include <vector>

#include "../graphics/Display.hpp"

#include <SDL2/SDL.h>
#include "Node.hpp"

PacketTransfer::PacketTransfer(Packet &p)
  : packet(p), progress(0.0f) {}

PacketTransfer &PacketTransfer::operator=(const PacketTransfer &other) {
  packet = other.packet;
  progress = other.progress;
  return *this;
}

Connection::Connection(std::weak_ptr<Node> nodeSrc, std::weak_ptr<Node> nodeDst, double deltaProgress) : nodeSrc(nodeSrc), nodeDst(nodeDst), deltaProgress(deltaProgress) {}

void Connection::doTick() {
  for (unsigned i = 0; i < mPackets.size(); i++) {
    mPackets[i].progress += deltaProgress;
    if (mPackets[i].progress > 1.0f) {
      auto x = mPackets.begin() + (i--);
      mPackets.erase(x);
    }
  }
}

void Connection::sendPacket(Packet &packet, Node *node) {
  if (node != nodeSrc.lock().get()) {
    throw new std::runtime_error("Invalid source node!");
  }

  mPackets.push_back({packet});
}

void Connection::doRender() {
  auto r = Display::inst->m_renderer;

  SDL_RenderDrawLine(r, nodeSrc.lock()->x, nodeSrc.lock()->y, nodeDst.lock()->x, nodeDst.lock()->y);
}

// vim: sw=2 et
