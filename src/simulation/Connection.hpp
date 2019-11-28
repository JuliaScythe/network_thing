#pragma once

#include <string>
#include "Node.hpp"
#include "SimObject.hpp"
#include <memory>
#include "Packet.hpp"

class Packet;

struct PacketTransfer {
  PacketTransfer(Packet &p);

  Packet &packet;
  float progress; // Ranges from 0 to 1
};

class Node;
class Connection : public SimObject {
public:
  Connection(std::weak_ptr<Node> nodeA, std::weak_ptr<Node> nodeB);
  void DoTick();

  std::weak_ptr<Node> nodeSrc;

  std::weak_ptr<Node> nodeDst;
  
  std::vector<PacketTransfer> mPackets;

  void sendPacket(Packet &packet, Node *node);

};

// vim: sw=2 et
