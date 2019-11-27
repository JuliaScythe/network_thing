#pragma once

#include <string>
#include "Node.hpp"
#include "SimObject.hpp"
#include <memory>
#include "Packet.hpp"
class Node;
class Connection : public SimObject {
public:
  Connection(std::weak_ptr<Node> nodeA, std::weak_ptr<Node> nodeB);
  void DoTick();

  std::weak_ptr<Node> nodeA;

  std::weak_ptr<Node> nodeB;
  
  int mLength;
  std::vector<Packet> mPackets;
  std::vector<int> mPacketDistances;

  void sendPacket(Packet &packet, Node *node);

};

