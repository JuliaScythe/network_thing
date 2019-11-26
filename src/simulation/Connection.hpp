#pragma once

#include <string>
#include "Node.hpp"

class Node;
class Connection {
public:
  Connection(Node &nodeA, Node &nodeB);

private:
  Node &nodeA;
  Node &nodeB;
  std::string name; 
};

