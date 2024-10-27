#include "car.h"

#include <cmath>

Car::Car(Position startPosition)
    : position_{startPosition}, velocity_(0), angle_(0), acceleration_(0) {}

void Car::HandleInput(const Uint8 *keyState) {
  acceleration_ = 0;

  if (keyState[SDL_SCANCODE_UP]) {
    acceleration_ = ACCELERATION;
  }
  if (keyState[SDL_SCANCODE_DOWN]) {
    acceleration_ = -ACCELERATION;
  }

  float turnFactor = std::abs(velocity_) / MAX_VELOCITY;
  if (std::abs(velocity_) > MIN_TURN_VELOCITY) {
    if (keyState[SDL_SCANCODE_LEFT]) {
      angle_ -= TURN_SPEED * turnFactor * (velocity_ > 0 ? 1.0F : -0.5F);
    }
    if (keyState[SDL_SCANCODE_RIGHT]) {
      angle_ += TURN_SPEED * turnFactor * (velocity_ > 0 ? 1.0F : -0.5F);
    }
  }
}

void Car::Update(float deltaTime) {
  velocity_ += acceleration_ * deltaTime;
  velocity_ *= FRICTION;

  if (velocity_ > MAX_VELOCITY)
    velocity_ = MAX_VELOCITY;
  if (velocity_ < -MAX_VELOCITY / 2)
    velocity_ = -MAX_VELOCITY / 2;

  position_.x += std::cos(angle_) * velocity_ * deltaTime;
  position_.y += std::sin(angle_) * velocity_ * deltaTime;
}

void Car::Render(SDL_Renderer *renderer) const {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  const int size = 20;
  SDL_Point points[3] = {
      {static_cast<int>(position_.x + std::cos(angle_) * size),
       static_cast<int>(position_.y + std::sin(angle_) * size)},
      {static_cast<int>(position_.x + std::cos(angle_ + 2.5) * size / 2),
       static_cast<int>(position_.y + std::sin(angle_ + 2.5) * size / 2)},
      {static_cast<int>(position_.x + std::cos(angle_ - 2.5) * size / 2),
       static_cast<int>(position_.y + std::sin(angle_ - 2.5) * size / 2)}};

  SDL_RenderDrawLines(renderer, points, 3);
  SDL_RenderDrawLine(renderer, points[2].x, points[2].y, points[0].x,
                     points[0].y);
}
