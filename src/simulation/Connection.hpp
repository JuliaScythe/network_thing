#pragma once

#include <string>
#include "Node.hpp"


class Connection {
public:
  Connection();
  Connection(Node &nodeA, Node &nodeB);

private:
  Node &nodeA;
  Node &nodeB;
  std::string name 
}

