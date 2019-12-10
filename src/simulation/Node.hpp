#pragma once

#include <chrono>
#include <vector>
#include <SDL2/SDL.h>
#include "Connection.hpp"
#include "SimObject.hpp"
#include "Packet.hpp"

class Packet;
class Connection;
class Node : public SimObject {
public:
  Node(int x, int y, int width);
  
  virtual void doTick();
  virtual void doRender();
  std::vector<Connection *> connections;
  void receivePacket(Packet &p, Connection *c);
  virtual void handlePacket(Packet &p, Connection *c);
  virtual void forwardPacket(Packet &p, Connection *c);

  virtual int sizeX();
  virtual int sizeY();
  
  std::string mName;
  int mX;
  int mY;
  float mScale;

private:
  int m_width;
  std::chrono::system_clock::time_point mTickRenderTime;
};

// vim: sw=2 et
