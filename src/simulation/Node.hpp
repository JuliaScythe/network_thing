#pragma once

#include <vector>
#include "Connection.hpp"
#include "SimObject.hpp"

class Connection;
class Node : public SimObject {
public:
  Node(int x, int y, int sizeX, int sizeY, int r, int g, int b, int a);
  
  void DoTick();
  void addConnection(Connection connection);
  std::vector<Connection> getConnections();
  std::vector<Connection> connections;
  
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

    

// vim: et sw=2
