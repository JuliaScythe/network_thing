#include "Simulation.hpp"


void Simulation::doTick() {
	for (auto &x : objects) {
		x->doTick();
	}
}

void Simulation::addObject(std::shared_ptr<SimObject> object) {
  objects.push_back(object);
}

// vim: sw=2 et
