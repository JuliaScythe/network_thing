#pragma once

#include <string>
#include "Node.hpp"
#include "SimObject.hpp"
#include <memory>

class Node;
class Connection : public SimObject {
public:
  Connection(std::weak_ptr<Node> nodeA, std::weak_ptr<Node> nodeB);
  void DoTick();

  std::weak_ptr<Node> nodeA;

  std::weak_ptr<Node> nodeB;
  
  int mLength;
  std::vector<std::shared_ptr<Packet>> mPackets;
  std::vector<int> mPacketDistances;

  void sendPacket();
};

