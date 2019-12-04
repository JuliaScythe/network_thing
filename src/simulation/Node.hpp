#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "Connection.hpp"
#include "SimObject.hpp"
#include "Packet.hpp"

class Packet;
class Connection;
class Node : public SimObject {
public:
  Node(int x, int y, int sizeX, int sizeY);
  
  void doTick();
  void doRender();
  std::vector<Connection *> connections;
  void receivePacket(Packet &p);
  virtual void handlePacket(Packet &p);
  virtual void forwardPacket(Packet &p);
  
  std::string name;
  int x;
  int y;
  int sizeX;
  int sizeY;

private:
  static SDL_Texture *m_texture;
};

// vim: sw=2 et
