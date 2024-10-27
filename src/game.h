#pragma once

#include "car.h"

#include <memory>

class Game {
public:
  Game();
  ~Game();

  bool Initialize();
  void Run();
  void Shutdown();

private:
  void HandleEvents();
  void Update();
  void Render();

private:
  SDL_Window *window_;
  SDL_Renderer *renderer_;
  bool isRunning_;
  std::unique_ptr<Car> car_;
  Uint32 lastFrame_;
};
