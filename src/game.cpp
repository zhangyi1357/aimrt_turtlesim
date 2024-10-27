#include "game.h"

Game::Game()
    : window_(nullptr), renderer_(nullptr), isRunning_(false), lastFrame_(0) {}

Game::~Game() { Shutdown(); }

bool Game::Initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    return false;
  }

  window_ =
      SDL_CreateWindow("Racing Game", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

  if (!window_) {
    return false;
  }

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!renderer_) {
    return false;
  }

  car_ = std::make_unique<Car>(400, 300);
  isRunning_ = true;
  lastFrame_ = SDL_GetTicks();

  return true;
}

void Game::HandleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning_ = false;
    }
  }

  const Uint8 *keyState = SDL_GetKeyboardState(nullptr);
  car_->HandleInput(keyState);
}

void Game::Update() {
  Uint32 current = SDL_GetTicks();
  float deltaTime = static_cast<float>(current - lastFrame_) / 1000.0F;
  lastFrame_ = current;

  car_->Update(deltaTime);
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);

  car_->Render(renderer_);

  SDL_RenderPresent(renderer_);
}

void Game::Run() {
  while (isRunning_) {
    HandleEvents();
    Update();
    Render();
  }
}

void Game::Shutdown() {
  if (renderer_) {
    SDL_DestroyRenderer(renderer_);
  }
  if (window_) {
    SDL_DestroyWindow(window_);
  }
  SDL_Quit();
}
