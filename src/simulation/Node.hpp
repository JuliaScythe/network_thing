#pragma once

#include <vector>
#include "Connection.hpp"
class Connection;
class Node {
public:
  Node(std::vector<Connection> connections);
  ~Node();

  void addConnection(Connection connection);
  std::vector<Connection> getConnections();
private:
  std::vector<Connection> connections;
  std::string name;
};
// vim: et sw=2
