#pragma once

#include <vector>
#include "Connection.hpp"
#include "SimObject.hpp"

class Connection;
class Node : public SimObject {
public:
  Node(std::vector<Connection> connections);
  ~Node();
  
  void DoTick();
  void addConnection(Connection connection);
  std::vector<Connection> getConnections();
private:
  std::vector<Connection> connections;
  std::string name;
  
};
// vim: et sw=2
