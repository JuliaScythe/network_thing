#pragma once

#include <vector>
#include <memory>
#include "SimObject.hpp"
#include "Packet.hpp"

struct PacketTransfer {
  PacketTransfer(Packet &p);

  PacketTransfer &operator=(const PacketTransfer &other);

  Packet &packet;
  float progress; // Ranges from 0 to 1
};

class Node;
class Connection : public SimObject {
public:
  Connection(std::weak_ptr<Node> nodeA, std::weak_ptr<Node> nodeB, double deltaProgress);
  void doTick();
  void doRender();
  std::weak_ptr<Node> nodeSrc;

  std::weak_ptr<Node> nodeDst;
  
  double deltaProgress; 
  std::vector<PacketTransfer> mPackets;

  void sendPacket(Packet &packet, Node *node);

};

// vim: sw=2 et
