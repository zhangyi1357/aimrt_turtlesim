#pragma once

#include <SDL.h>

struct Position {
  float x;
  float y;
};

class Car {
public:
  explicit Car(Position startPosition);
  void HandleInput(const Uint8 *keyState);
  void Update(float deltaTime);
  void Render(SDL_Renderer *renderer) const;

private:
  Position position_;
  float velocity_;
  float angle_; // in radians
  float acceleration_;

  static constexpr const float MAX_VELOCITY = 300.0F;
  static constexpr const float ACCELERATION = 200.0F;
  static constexpr const float TURN_SPEED = 0.1F;
  static constexpr const float FRICTION = 0.98F;
  static constexpr const float MIN_TURN_VELOCITY = 0.0F;
};
