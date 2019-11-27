#include "simulation/Simulation.hpp"
#include "simulation/Node.hpp"

int main() {
  auto networkSim = Simulation();
  networkSim.addObject(std::shared_ptr<SimObject>(new Node(100, 100, 10, 10, 255, 255, 0, 255)));
}
