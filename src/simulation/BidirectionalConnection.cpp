#include "BidirectionalConnection.hpp"
#include "Node.hpp"
#include "../graphics/Display.hpp"

void BidirectionalConnection::sendPacket(Packet &packet, Node *node) {
  if (node == mNodeA.lock().get()) {
    mPackets.push_back(packet);
  } else if (node == mNodeB.lock().get()) {
    mReversePackets.push_back(packet);
  } else {
    throw new std::runtime_error("Invalid source node!");
  }
}

void BidirectionalConnection::doTick() {
  Connection::doTick(); // Ensure the forward packets are moved forward

  float deltaProg = scaledDeltaProgress();

  // Move the reverse packets forward
  for (unsigned i = 0; i < mReversePackets.size(); i++) {
    mReversePackets[i].progress += deltaProg;
    if (mReversePackets[i].progress > 1.0f) {
      mNodeA.lock()->receivePacket(mReversePackets[i].packet, this);
      auto x = mReversePackets.begin() + (i--);
      mReversePackets.erase(x);
    }
  }
}

void BidirectionalConnection::doRender() {
  Connection::doRender();

  auto r = Display::inst->m_renderer;

  int x2 = mNodeA.lock()->mX + mNodeA.lock()->sizeX() / 2;
  int y2 = mNodeA.lock()->mY + mNodeA.lock()->sizeY() / 2;
  int x1 = mNodeB.lock()->mX + mNodeB.lock()->sizeX() / 2;
  int y1 = mNodeB.lock()->mY + mNodeB.lock()->sizeY() / 2;

  SDL_SetRenderDrawColor(r, 255, 0, 0, 255);

  for (auto &p : mReversePackets) {
    SDL_Rect rect;
    rect.x = x1 + (x2 - x1) * p.progress - 25;
    rect.y = y1 + (y2 - y1) * p.progress - 25;
    rect.w = 50;
    rect.h = 50;
    SDL_RenderFillRect(r, &rect);
  }
}


bool BidirectionalConnection::isSrc(Node *n) {
  return n == mNodeA.lock().get() || n == mNodeB.lock().get();
}

bool BidirectionalConnection::isDst(Node *n) {
  return n == mNodeA.lock().get() || n == mNodeB.lock().get();
}
