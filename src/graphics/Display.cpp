#include "Display.hpp"
#include "Texture.hpp"
#include "../simulation/nodes/Hub.hpp"
#include "../simulation/Simulation.hpp"
#include "../simulation/Node.hpp"
#include "../simulation/Connection.hpp"
#include "../simulation/BidirectionalConnection.hpp"
#include "../locking_ptr.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <cmath>
#include <thread>
#include <mutex>
#include <algorithm>
#include <iostream>
#define TICK_PER_SECOND 100
#define FRAME_PER_SECOND 60

Display *Display::inst = nullptr;

Display::Display(const char *title, int width, int height) {
  Display::inst = this;

  if (SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(SDL_GetError());
  }

  m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

  if (!m_window) {
    throw std::runtime_error(SDL_GetError());
  }

  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

  Texture::initAll();
}

static void tickingThread() {
  using tickDuration = std::chrono::duration<int64_t, std::ratio<1, TICK_PER_SECOND>>;

  auto next = std::chrono::system_clock::now();
  auto last = next - tickDuration{1};
  while (!Display::inst->m_close) {
    std::this_thread::sleep_until(next);
    Display::inst->doTick();
    last = next;
    next += tickDuration{1};
  }
}

static void packetThread(std::vector<std::shared_ptr<Node>> nodes, std::vector<std::shared_ptr<BidirectionalConnection>> conns) {
  auto next = std::chrono::system_clock::now();
  auto last = next;
  while (!Display::inst->m_close) {
    std::this_thread::sleep_until(next);

    size_t a = std::rand() % nodes.size();
    size_t b = std::rand() % nodes.size();

    Packet p(nodes[a], nodes[b], 16, {0});
    conns[a]->sendPacket(p, nodes[a].get());

    last = next;

    size_t n = std::rand() % 9 + 2;
    next += std::chrono::duration<int64_t, std::ratio<1, 2>>{n};
  }
}

void Display::doTick() {
  for (auto &obj : m_sim.lock()->mObjects) {
    obj->doTick();
  }
}

void Display::mainLoop() {
  std::shared_ptr<NodeHub> h1 = std::make_shared<NodeHub>(400, 700, 40);

  std::shared_ptr<Node> n1 = std::make_shared<Node>(350, 400, 30);
  std::shared_ptr<BidirectionalConnection> c1 = std::make_shared<BidirectionalConnection>(n1, h1, 1.5f);
  std::shared_ptr<Node> n2 = std::make_shared<Node>(200, 500, 30);
  std::shared_ptr<BidirectionalConnection> c2 = std::make_shared<BidirectionalConnection>(n2, h1, 1.5f);
  std::shared_ptr<Node> n3 = std::make_shared<Node>(100, 700, 30);
  std::shared_ptr<BidirectionalConnection> c3 = std::make_shared<BidirectionalConnection>(n3, h1, 1.5f);
  std::shared_ptr<Node> n4 = std::make_shared<Node>(200, 900, 30);
  std::shared_ptr<BidirectionalConnection> c4 = std::make_shared<BidirectionalConnection>(n4, h1, 1.5f);
  std::shared_ptr<Node> n5 = std::make_shared<Node>(350, 1000, 30);
  std::shared_ptr<BidirectionalConnection> c5 = std::make_shared<BidirectionalConnection>(n5, h1, 1.5f);

  std::shared_ptr<NodeHub> h2 = std::make_shared<NodeHub>(1024-400, 700, 40);

  std::shared_ptr<Node> n6 = std::make_shared<Node>(1024-350, 400, 30);
  std::shared_ptr<BidirectionalConnection> c6 = std::make_shared<BidirectionalConnection>(n6, h2, 1.5f);
  std::shared_ptr<Node> n7 = std::make_shared<Node>(1024-200, 500, 30);
  std::shared_ptr<BidirectionalConnection> c7 = std::make_shared<BidirectionalConnection>(n7, h2, 1.5f);
  std::shared_ptr<Node> n8 = std::make_shared<Node>(1024-100, 700, 30);
  std::shared_ptr<BidirectionalConnection> c8 = std::make_shared<BidirectionalConnection>(n8, h2, 1.5f);
  std::shared_ptr<Node> n9 = std::make_shared<Node>(1024-200, 900, 30);
  std::shared_ptr<BidirectionalConnection> c9 = std::make_shared<BidirectionalConnection>(n9, h2, 1.5f);
  std::shared_ptr<Node> n10 = std::make_shared<Node>(1024-350, 1000, 30);
  std::shared_ptr<BidirectionalConnection> c10 = std::make_shared<BidirectionalConnection>(n10, h2, 1.5f);

  std::shared_ptr<BidirectionalConnection> ch = std::make_shared<BidirectionalConnection>(h1, h2, 1.5f);

  m_sim.lock()->addObject(n1);
  m_sim.lock()->addObject(n2);
  m_sim.lock()->addObject(n3);
  m_sim.lock()->addObject(n4);
  m_sim.lock()->addObject(n5);
  m_sim.lock()->addObject(n6);
  m_sim.lock()->addObject(n7);
  m_sim.lock()->addObject(n8);
  m_sim.lock()->addObject(n9);
  m_sim.lock()->addObject(n10);
  m_sim.lock()->addObject(c1);
  m_sim.lock()->addObject(c2);
  m_sim.lock()->addObject(c3);
  m_sim.lock()->addObject(c4);
  m_sim.lock()->addObject(c5);
  m_sim.lock()->addObject(c6);
  m_sim.lock()->addObject(c7);
  m_sim.lock()->addObject(c8);
  m_sim.lock()->addObject(c9);
  m_sim.lock()->addObject(c10);
  m_sim.lock()->addObject(h1);
  m_sim.lock()->addObject(h2);
  m_sim.lock()->addObject(ch);

  std::thread ticker(tickingThread);
  std::thread packeter(packetThread, std::vector<std::shared_ptr<Node>>{n1, n2, n3, n4, n5, n6, n7, n8, n9, n10}, std::vector<std::shared_ptr<BidirectionalConnection>>{c1, c2, c3, c4, c5, c6, c7, c8, c9, c10});

  using frameDuration = std::chrono::duration<int64_t, std::ratio<1, FRAME_PER_SECOND>>;

  auto next = std::chrono::system_clock::now() + frameDuration{0};
  auto last = next - frameDuration{1};

  while (!m_close) {
    std::this_thread::sleep_until(next);

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);
    
    for (auto &obj : m_sim.lock()->mObjects) {
      obj->doRender();
    }

    update();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        m_close = true;
      }
    }

    last = next;
    next += frameDuration{1};
  }

  ticker.join();
  packeter.join();
}

SDL_Texture *Display::createTexture(const char *path) {
  SDL_RWops *rwops = SDL_RWFromFile(path, "r");
  if (!rwops) {
    throw std::runtime_error(SDL_GetError());
  }

  SDL_Surface *img = IMG_LoadSVG_RW(rwops);
  if (!img) {
    throw std::runtime_error(IMG_GetError());
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, img);
  if (!texture) {
    throw std::runtime_error(SDL_GetError());
  }

  return texture;
}

void Display::update() {
  SDL_RenderPresent(m_renderer);
}

Display::~Display() {
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

// vim: sw=2 et
