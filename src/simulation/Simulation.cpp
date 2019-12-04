#include "Simulation.hpp"
#include <algorithm>

void Simulation::doTick() {
	for (auto &x : mObjects) {
		x->doTick();
	}
}

void Simulation::addObject(std::shared_ptr<SimObject> object) {
  mObjects.push_back(object); 
  std::sort(mObjects.begin(), mObjects.end(), SimObject::compareLayers);
}

// vim: sw=2 et
