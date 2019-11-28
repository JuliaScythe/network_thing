#pragma once

#include "SimObject.hpp"
#include <vector>
#include <memory>

class Simulation {
public:
  void addObject(std::shared_ptr<SimObject> object);

  std::vector<std::shared_ptr<SimObject>> objects;
  void DoTick();
};

// vim: sw=2 et
