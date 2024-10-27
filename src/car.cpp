#include "car.h"

#include <algorithm>
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

  velocity_ = std::clamp(velocity_, -MAX_VELOCITY / 2, MAX_VELOCITY);

  position_.x += std::cos(angle_) * velocity_ * deltaTime;
  position_.y += std::sin(angle_) * velocity_ * deltaTime;
}

void Car::Render(SDL_Renderer *renderer) const {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  const float size = 20.0F;
  SDL_Point points[3] = {};
  const float angles[3] = {
      angle_,        // front vertex
      angle_ + 2.5F, // back right vertex
      angle_ - 2.5F  // back left vertex
  };
  const float sizes[3] = {
      size,     // front vertex distance
      size / 2, // back vertices distance
      size / 2  // back vertices distance
  };
  for (int i = 0; i < 3; ++i) {
    points[i] = {
        static_cast<int>(position_.x + std::cos(angles[i]) * sizes[i]),
        static_cast<int>(position_.y + std::sin(angles[i]) * sizes[i])};
  }

  SDL_RenderDrawLines(renderer, points, 3);
  SDL_RenderDrawLine(renderer, points[2].x, points[2].y, points[0].x,
                     points[0].y);
}
