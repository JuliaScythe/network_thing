#pragma once

#include <vector>
#include <memory>
#include "SimObject.hpp"
#include "Packet.hpp"

struct PacketTransfer {
  PacketTransfer(Packet &p);

  PacketTransfer &operator=(const PacketTransfer &other);

  Packet packet;
  float progress; // Ranges from 0 to 1
};

class Node;
class Connection : public SimObject {
public:
  Connection(std::weak_ptr<Node> nodeA, std::weak_ptr<Node> nodeB, double deltaProgress);
  virtual void doTick();
  virtual void doRender();
  std::weak_ptr<Node> mNodeA;
  std::weak_ptr<Node> mNodeB;
  int getLayer();

  virtual bool isSrc(Node *n);
  virtual bool isDst(Node *n);
  
  double mDeltaProgress; 
  std::vector<PacketTransfer> mPackets;

  virtual void sendPacket(Packet &packet, Node *node);
};

// vim: sw=2 et
