#pragma once

#include <memory>
#include "Node.hpp"

class Packet {
public:
  Packet(std::weak_ptr<Node> src, std::weak_ptr<Node> dst, unsigned hopLimit, std::vector<unsigned char> payload);

  std::weak_ptr<Node> mSrc;
  std::weak_ptr<Node> mDst;
  unsigned mHopLimit;
  std::vector<unsigned char> mPayload;
};
