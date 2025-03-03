#pragma once

#include <functional>
#include <map>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "animation.hpp"
#include "animation_system.hpp"

struct Entity {
private:
  Vector2 position;
  Vector2 velocity;
  float speed;
  float scale;

  std::unique_ptr<AnimationSystem> animationSystem;

  std::vector<std::function<bool(Rectangle)>> collisionChecks;

  void SetupAnimationSystem() {
    animationSystem = std::make_unique<AnimationSystem>();
  }

public:
  enum AnimationType {
    WALK_RIGHT = 0,
    WALK_LEFT,
    WALK_UP,
    WALK_DOWN,
    IDLE_RIGHT,
    IDLE_LEFT,
    IDLE_UP,
    IDLE_DOWN,
    ATTACK_RIGHT,
    ATTACK_LEFT,
    ATTACK_UP,
    ATTACK_DOWN,
  };

  Entity(Vector2 position, Vector2 velocity, float speed, float scale)
      : position(position), velocity(velocity), speed(speed), scale(scale) {
     
  }

  virtual void Update(double deltaTime);
  virtual void Draw();
};

