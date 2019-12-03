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

  {
    SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
    int x1 = nodeSrc.lock()->x + nodeSrc.lock()->sizeX / 2;
    int y1 = nodeSrc.lock()->y + nodeSrc.lock()->sizeY / 2;
    int x2 = nodeDst.lock()->x + nodeDst.lock()->sizeX / 2;
    int y2 = nodeDst.lock()->y + nodeDst.lock()->sizeY / 2;
    SDL_RenderDrawLine(r, x1, y1, x2, y2);
  }

  SDL_SetRenderDrawColor(r, 255, 0, 0, 255);

  int startX = nodeSrc.lock()->x + nodeSrc.lock()->sizeX / 2;
  int startY = nodeSrc.lock()->y + nodeSrc.lock()->sizeY / 2;
  int endX = nodeDst.lock()->x + nodeDst.lock()->sizeX / 2;
  int endY = nodeDst.lock()->y + nodeDst.lock()->sizeY / 2;

  for (auto &p : mPackets) {
    SDL_Rect rect;
    rect.x = startX + (endX - startX) * p.progress - 25;
    rect.y = startY + (endY - startY) * p.progress - 25;
    rect.w = 50;
    rect.h = 50;
    SDL_RenderFillRect(r, &rect);
  }
}

// vim: sw=2 et
