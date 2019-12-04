#pragma once

#include "../Node.hpp"

class NodeHub : public Node {
public:
  using Node::Node;
  virtual void forwardPacket(Packet &p) override;
  virtual void doRender() override;
private:
  static SDL_Texture *s_texture;
  static int s_txt_width;
  static int s_txt_height;
};

// vim: sw=2 et
