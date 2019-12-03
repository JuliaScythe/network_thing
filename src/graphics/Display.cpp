#include "Display.hpp"
#include "../simulation/Simulation.hpp"
#include "../simulation/Node.hpp"
#include "../simulation/Connection.hpp"
#include "../locking_ptr.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>
#include <cmath>
#include <thread>
#include <mutex>

#define TICK_PER_SECOND 50

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

void Display::doTick() {
  for (auto &obj : m_sim.lock()->objects) {
    obj->doTick();
  }
}

void Display::mainLoop() {
  {
    std::shared_ptr<Node> n1 = std::make_shared<Node>(100, 100, 50, 50);
    std::shared_ptr<Node> n2 = std::make_shared<Node>(500, 300, 50, 50);
    std::shared_ptr<Connection> c = std::make_shared<Connection>(n1, n2, 0.01f);
    m_sim.lock()->addObject(n1);
    m_sim.lock()->addObject(n2);
    m_sim.lock()->addObject(c);
  }

  std::thread ticker(tickingThread);

  while (!m_close) {
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    for (auto &obj : m_sim.lock()->objects) {
      obj->doRender();
    }

    update();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        m_close = true;
      }
    }
  }

  ticker.join();
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
