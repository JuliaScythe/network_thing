#include "Packet.hpp"

Packet::Packet(std::weak_ptr<Node> src, std::weak_ptr<Node> dst, unsigned hopLimit, std::vector<unsigned char> payload)
  : mSrc(src), mDst(dst), mHopLimit(hopLimit), mPayload(payload) {}
