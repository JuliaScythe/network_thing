#pragma once

#include <memory>
#include <vector>

class Node;
class Packet {
public:
  Packet(std::weak_ptr<Node> src, std::weak_ptr<Node> dst, unsigned hopLimit, std::vector<unsigned char> payload);

  Packet &operator=(const Packet &other);

  std::weak_ptr<Node> mSrc;
  std::weak_ptr<Node> mDst;
  unsigned mHopLimit;
  std::vector<unsigned char> mPayload;
};

// vim: sw=2 et
