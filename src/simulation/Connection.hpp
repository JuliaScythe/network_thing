#pragma once

#include <string>
#include "Node.hpp"
#include "SimObject.hpp"

class Node;
class Connection : public SimObject {
public:
  Connection(Node &nodeA, Node &nodeB);
  void DoTick();

private:
  Node &nodeA;
  Node &nodeB;
  std::string name;
};

