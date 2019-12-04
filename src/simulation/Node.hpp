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
  Node(int x, int y, int width);
  
  void doTick();
  void doRender();
  std::vector<Connection *> connections;
  void receivePacket(Packet &p);
  virtual void handlePacket(Packet &p);
  virtual void forwardPacket(Packet &p);

  int sizeX();
  int sizeY();
  
  std::string mName;
  int mX;
  int mY;
  float mScale;

private:
  int m_width;

  static SDL_Texture *s_texture;
  static int s_txt_width;
  static int s_txt_height;
};

// vim: sw=2 et
