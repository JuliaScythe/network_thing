#pragma once

class SimObject {
public:	
  virtual void doTick() = 0;
  virtual void doRender();
};

// vim: sw=2 et
