#include "Simulation.hpp"


void Simulation::DoTick() {
	for (auto &x : objects) {
		x->DoTick();
	}
}

void Simulation::addObject(std::shared_ptr<SimObject> object) {
  objects.push_back(object);
}
