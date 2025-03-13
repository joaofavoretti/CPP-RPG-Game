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
  std::map<Entity *, std::function<void(Entity *)>> collisionCallbacks;

  Entity(Vector2 position, Vector2 velocity, float scale)
      : position(position), velocity(velocity), scale(scale) {}

  virtual ~Entity() = default;

  Vector2 GetPosition() { return position; }

  void SetupAnimationSystem() {
    animationSystem = std::make_unique<AnimationSystem>();
    RegisterAnimations();
  }

  void RegisterAnimation(EntityAnimationId id, AnimationConfig config) {
    animationSystem->RegisterAnimation(id, config);
  }

  void AddCollisionCallback(Entity *entity,
                            std::function<void(Entity *)> callback) {
    collisionCallbacks[entity] = callback;
  }

  void SetAnimation(EntityAnimationId id) { animationSystem->Update(id, 0); }

  void SetPosition(Vector2 position) { this->position = position; }

  virtual void RegisterAnimations() = 0;

  virtual Vector2 GetBoundaryCenter() {
    Rectangle boundaries = GetBoundaries();
    return {boundaries.x + boundaries.width / 2.0f,
            boundaries.y + boundaries.height / 2.0f};
  }

  virtual Rectangle GetBoundariesFromPosition(Vector2 position) {
    return Rectangle{
        .x = position.x,
        .y = position.y,
        .width = animationSystem->GetSize().x,
        .height = animationSystem->GetSize().y,
    };
  }

  virtual Rectangle GetBoundaries() {
    return GetBoundariesFromPosition(position);
  }

  virtual bool IsColliding(Rectangle rect) {
    return CheckCollisionRecs(GetBoundaries(), rect);
  }

  virtual void CheckCollisionCallbacks() {
    for (auto const &[entity, callback] : collisionCallbacks) {
      if (CheckCollisionRecs(GetBoundaries(), entity->GetBoundaries())) {
        callback(this);
      }
    }
  }

  virtual void Update(double deltaTime) {
    animationSystem->Update(deltaTime);
    animationSystem->SetPosition(position);

    CheckCollisionCallbacks();
  }

  virtual void Draw() {
#ifdef DEBUG
    DrawRectangleLinesEx(GetBoundaries(), 1, RED);
#endif

    animationSystem->Draw();
  }
};
