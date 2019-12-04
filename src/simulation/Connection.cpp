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

Connection::Connection(std::weak_ptr<Node> nodeA, std::weak_ptr<Node> nodeB, double deltaProgress)
    : mNodeA(nodeA), mNodeB(nodeB), mDeltaProgress(deltaProgress) {
  nodeA.lock()->connections.push_back(this);
  nodeB.lock()->connections.push_back(this);
}

void Connection::doTick() {
  for (unsigned i = 0; i < mPackets.size(); i++) {
    mPackets[i].progress += mDeltaProgress;
    if (mPackets[i].progress > 1.0f) {
      mNodeB.lock()->receivePacket(mPackets[i].packet, this);
      auto x = mPackets.begin() + (i--);
      mPackets.erase(x);
    }
  }
}

void Connection::sendPacket(Packet &packet, Node *node) {
  if (node != mNodeA.lock().get()) {
    throw new std::runtime_error("Invalid source node!");
  }

  mPackets.push_back({packet});
}

void Connection::doRender() {
  auto r = Display::inst->m_renderer;

  int x1 = mNodeA.lock()->mX + mNodeA.lock()->sizeX() / 2;
  int y1 = mNodeA.lock()->mY + mNodeA.lock()->sizeY() / 2;
  int x2 = mNodeB.lock()->mX + mNodeB.lock()->sizeX() / 2;
  int y2 = mNodeB.lock()->mY + mNodeB.lock()->sizeY() / 2;

  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
  SDL_RenderDrawLine(r, x1, y1, x2, y2);

  SDL_SetRenderDrawColor(r, 255, 0, 0, 255);

  for (auto &p : mPackets) {
    SDL_Rect rect;
    rect.x = x1 + (x2 - x1) * p.progress - 25;
    rect.y = y1 + (y2 - y1) * p.progress - 25;
    rect.w = 50;
    rect.h = 50;
    SDL_RenderFillRect(r, &rect);
  }
}

bool Connection::isSrc(Node *n) {
  return n == mNodeA.lock().get();
}

bool Connection::isDst(Node *n) {
  return n == mNodeB.lock().get();
}

int Connection::getLayer() {
  return -1;
}

// vim: sw=2 et
