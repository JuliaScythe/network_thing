#include "Packet.hpp"

Packet::Packet(std::weak_ptr<Node> src, std::weak_ptr<Node> dst, unsigned hopLimit, std::vector<unsigned char> payload)
  : mSrc(src), mDst(dst), mHopLimit(hopLimit), mPayload(payload) {}

Packet &Packet::operator=(const Packet &other) {
  mSrc = other.mSrc;
  mDst = other.mDst;
  mHopLimit = other.mHopLimit;
  mPayload = other.mPayload;
  return *this;
}

// vim: sw=2 et
