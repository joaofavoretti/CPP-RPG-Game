#pragma once

#include <functional>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "animation_system.hpp"

struct Entity {
  enum EntityAnimationId {
    MOVE = 0,
    MOVE_RIGHT,
    MOVE_LEFT,
    MOVE_UP,
    MOVE_DOWN,
    IDLE,
    IDLE_RIGHT,
    IDLE_LEFT,
    IDLE_UP,
    IDLE_DOWN,
    ATTACK,
    ATTACK_RIGHT,
    ATTACK_LEFT,
    ATTACK_UP,
    ATTACK_DOWN,
  };

  Vector2 position;
  Vector2 velocity;
  float scale;

  std::unique_ptr<AnimationSystem> animationSystem;
  std::vector<std::function<void(Rectangle)>> collisionCallbacks;

  Entity(Vector2 position, Vector2 velocity, float scale)
      : position(position), velocity(velocity), scale(scale) {
  }

  virtual ~Entity() = default;

  Vector2 GetPosition() { return position; }

  void AddCollisionCallback(std::function<void(Rectangle)> collisionCallback) {
    collisionCallbacks.push_back(collisionCallback);
  }

  void SetupAnimationSystem() {
    animationSystem = std::make_unique<AnimationSystem>();
    RegisterAnimations();
  }

  void RegisterAnimation(EntityAnimationId id, AnimationConfig config) {
    animationSystem->RegisterAnimation(id, config);
  }

  void SetAnimation(EntityAnimationId id) { animationSystem->Update(id, 0); }

  virtual void RegisterAnimations() = 0;

  virtual Rectangle GetBoundaries() {
    return Rectangle{
        .x = position.x,
        .y = position.y,
        .width = animationSystem->GetSize().x,
        .height = animationSystem->GetSize().y,
    };
  }

  virtual bool IsColliding(Rectangle rect) {
    return CheckCollisionRecs(GetBoundaries(), rect);
  }

  virtual void Update(double deltaTime) {
    animationSystem->Update(deltaTime);
    animationSystem->SetPosition(position);
  }

  virtual void Draw() {
#ifdef DEBUG
    DrawRectangleLinesEx(GetBoundaries(), 1, RED);
#endif

    animationSystem->Draw();
  }
};
