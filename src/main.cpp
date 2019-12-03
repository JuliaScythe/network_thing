#include "simulation/Simulation.hpp"
#include "simulation/Node.hpp"

#include "graphics/Display.hpp"

#include <iostream>

int main() {
  Display display("Network Display", 800, 600);
  
  display.mainLoop();

  std::cout << "Done" << std::endl;

  return 0;
}

// vim: sw=2 et
