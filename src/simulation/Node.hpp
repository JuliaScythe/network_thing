#pragma once

#include <vector>
#include "Connection.hpp"
#include "SimObject.hpp"
#include "Packet.hpp"

class Packet;
class Connection;
class Node : public SimObject {
public:
  Node(int x, int y, int sizeX, int sizeY, int r, int g, int b, int a);
  
  void DoTick();
  void addConnection(Connection connection);
  std::vector<Connection> getConnections();
  std::vector<Connection> connections;
  void receivePacket(Packet &p);
  virtual void handlePacket(Packet &p);
  virtual void forwardPacket(Packet &p);
  
  std::string name;
  int x;
  int y;
  int sizeX;
  int sizeY;
  int r;
  int g;
  int b;
  int a;
  
};

// vim: sw=2 et
