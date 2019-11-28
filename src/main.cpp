#include "simulation/Simulation.hpp"
#include "simulation/Node.hpp"

#include "graphics/Display.hpp"

#include <iostream>

int main() {
  Simulation networkSim;
  
  auto node1 = std::make_shared<Node>(100, 100, 10, 10, 255, 255, 0, 255);
  auto node2 = std::make_shared<Node>(200, 200, 10, 10, 255, 255, 0, 255);
  auto node3 = std::make_shared<Node>(300, 300, 10, 10, 255, 255, 0, 255);

  networkSim.addObject(node1);
  networkSim.addObject(node2);
  networkSim.addObject(node3);

  auto connection1 = std::shared_ptr<SimObject>(new Connection(node1, node2));

  networkSim.addObject(connection1);
  
  Display display("foobar", 800, 600);
  
  networkSim.DoTick();
}

// vim: sw=2 et
