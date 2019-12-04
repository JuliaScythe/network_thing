#pragma once
#include <memory>
class SimObject {
public:	
  virtual void doTick() = 0;
  virtual void doRender();

  virtual int getLayer();

  static bool compareLayers(std::shared_ptr<SimObject> a, std::shared_ptr<SimObject> b);
};

// vim: sw=2 et
