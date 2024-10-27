#pragma once

#include <SDL.h>

class Car {
public:
  Car(float startX, float startY);
  void HandleInput(const Uint8 *keyState);
  void Update(float deltaTime);
  void Render(SDL_Renderer *renderer) const;

private:
  float x_, y_;        // 位置
  float velocity_;     // 速度
  float angle_;        // 角度（弧度）
  float acceleration_; // 加速度

  static constexpr const float MAX_VELOCITY = 300.0F; // 最大速度
  static constexpr const float ACCELERATION = 200.0F; // 加速度大小
  static constexpr const float TURN_SPEED = 0.1F; // 降低基础转向速度
  static constexpr const float FRICTION = 0.98F;  // 摩擦系数
  static constexpr const float MIN_TURN_VELOCITY = 0.0F; // 最小转向速度阈值
};
