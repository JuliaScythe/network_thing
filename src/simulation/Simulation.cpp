#include "Simulation.hpp"


void Simulation::doTick() {
	for (auto &x : mObjects) {
		x->doTick();
	}
}

void Simulation::addObject(std::shared_ptr<SimObject> object) {
  mObjects.push_back(object);
}

// vim: sw=2 et
