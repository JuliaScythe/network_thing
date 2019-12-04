#include "SimObject.hpp"
#include <memory>
#include <iostream>
void SimObject::doRender() {}

int SimObject::getLayer() {
    return 0;
}

bool SimObject::compareLayers(std::shared_ptr<SimObject> a, std::shared_ptr<SimObject> b) {
  if (a->getLayer() == b->getLayer()) return false;
  return (a->getLayer() < b->getLayer()); 
}

// vim: sw=2 et
