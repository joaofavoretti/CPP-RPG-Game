#pragma once

#include <raylib.h>
#include <raymath.h>
#include <set>
#include <iostream>

#include "entity.hpp"

#define ENEMY_ANIMATION_BASE_PATH "../assets/pixel_art/3 Dungeon Enemies/1"

struct Enemy : Entity {

  float speed = 30.0f;
  Entity *target = nullptr;
  std::set<Entity *> possibleTargets;
  int attackDamage = 10;
  float attackRange = 5.0f;
  float followRange = 50.0f;

  Entity::EntityAnimationId lastMoveAnimation =
      Entity::EntityAnimationId::MOVE_RIGHT;

protected:
  void RegisterAnimations() override {
    RegisterAnimation(
        Entity::EntityAnimationId::MOVE_RIGHT,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Walk.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 6,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = true,
            .flip = true,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::MOVE_LEFT,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Walk.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 6,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = true,
            .flip = false,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::MOVE_UP,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/U_Walk.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 6,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = true,
            .flip = false,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::MOVE_DOWN,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/D_Walk.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 6,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = true,
            .flip = false,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::IDLE_RIGHT,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Idle.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 4,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = true,
            .flip = true,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::IDLE_LEFT,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Idle.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 4,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = true,
            .flip = false,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::IDLE_UP,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/U_Idle.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 4,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = true,
            .flip = false,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::IDLE_DOWN,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/D_Idle.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 4,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = true,
            .flip = false,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::ATTACK_RIGHT,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Attack.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 4,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = false,
            .flip = true,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::ATTACK_LEFT,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Attack.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 4,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = false,
            .flip = false,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::ATTACK_UP,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/U_Attack.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 4,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = false,
            .flip = false,
        });

    RegisterAnimation(
        Entity::EntityAnimationId::ATTACK_DOWN,
        AnimationConfig{
            .texturePath = ENEMY_ANIMATION_BASE_PATH "/D_Attack.png",
            .textureTileSize = {32, 32},
            .texturePosition = {0, 0},
            .numberOfFrames = 4,
            .frameSpeed = 0.1f,
            .scale = scale,
            .loop = false,
            .flip = false,
        });
  }

public:
  Enemy(Vector2 position) : Entity(position, Vector2{0, 0}, 1.0f) {
    SetupAnimationSystem();
  }

  Rectangle GetBoundaries() override {
    return GetBoundariesFromPosition(position);
  }

  Rectangle GetBoundariesFromPosition(Vector2 position) {
    Rectangle boundaries = {
        .x = 0,
        .y = 12,
        .width = static_cast<float>(animationSystem->GetSize().x * 2.1 / 3),
        .height = animationSystem->GetSize().y / 4,
    };

    return Rectangle{
        .x = position.x + boundaries.x,
        .y = position.y + boundaries.y,
        .width = boundaries.width,
        .height = boundaries.height,
    };
  }

  void UpdateFollowTarget(double deltaTime) {
    if (possibleTargets.empty()) {
      return;
    }

    if (target != nullptr) {
      if (Vector2Distance(target->GetPosition(), position) > followRange) {
        target = nullptr;
      }
    }

    if (target == nullptr) {
      Entity *closestTarget = nullptr;
      float closestDistance = followRange;

      for (auto possibleTarget : possibleTargets) {
        float distance =
            Vector2Distance(possibleTarget->GetPosition(), position);
        if (distance < closestDistance) {
          closestDistance = distance;
          closestTarget = possibleTarget;
        }
      }

      target = closestTarget;
    }
  }

  void UpdateLastAnimationFromVelocity(double deltaTime) {
    if (Vector2Length(velocity) == 0) {
      return;
    }

    Entity::EntityAnimationId movementMap[] = {
        Entity::EntityAnimationId::MOVE_RIGHT,
        Entity::EntityAnimationId::MOVE_DOWN,
        Entity::EntityAnimationId::MOVE_LEFT,
        Entity::EntityAnimationId::MOVE_UP,
    };

    float angle = atan2(velocity.y, velocity.x);
    if (angle < 0) angle += 2 * PI;
    angle += PI / 4;
    angle = fmod(angle, 2 * PI);
    int index = static_cast<int>(angle / (PI / 2));
    lastMoveAnimation = movementMap[index];
  }

  void UpdateVelocity(double deltaTime) {
    // Set the velocity accordingly
    if (target == nullptr) {
      velocity = {0.0f, 0.0f};
      return;
    }

    // Simple follow target for now. Make a wall detection later, maybe
    Vector2 direction =
        Vector2Normalize(Vector2Subtract(target->GetPosition(), position));
    velocity = Vector2Scale(direction, speed * deltaTime);
  }

  void UpdateAnimationSystem(double deltaTime) {
    std::map<Entity::EntityAnimationId, Entity::EntityAnimationId>
        idleAnimationsMap = {{Entity::EntityAnimationId::MOVE_RIGHT,
                              Entity::EntityAnimationId::IDLE_RIGHT},
                             {Entity::EntityAnimationId::MOVE_LEFT,
                              Entity::EntityAnimationId::IDLE_LEFT},
                             {Entity::EntityAnimationId::MOVE_UP,
                              Entity::EntityAnimationId::IDLE_UP},
                             {Entity::EntityAnimationId::MOVE_DOWN,
                              Entity::EntityAnimationId::IDLE_DOWN}};

    std::map<Entity::EntityAnimationId, Entity::EntityAnimationId>
        attackAnimationsMap = {{Entity::EntityAnimationId::MOVE_RIGHT,
                                Entity::EntityAnimationId::ATTACK_RIGHT},
                               {Entity::EntityAnimationId::MOVE_LEFT,
                                Entity::EntityAnimationId::ATTACK_LEFT},
                               {Entity::EntityAnimationId::MOVE_UP,
                                Entity::EntityAnimationId::ATTACK_UP},
                               {Entity::EntityAnimationId::MOVE_DOWN,
                                Entity::EntityAnimationId::ATTACK_DOWN}};

    if (Vector2Length(velocity) == 0) {
      animationSystem->Update(idleAnimationsMap[lastMoveAnimation], deltaTime);
    } else {
      animationSystem->Update(lastMoveAnimation, deltaTime);
    }

    if (IsKeyDown(KEY_SPACE)) {
      animationSystem->Update(attackAnimationsMap[lastMoveAnimation],
                              deltaTime);
    }

    animationSystem->SetPosition(position);
  }

  void AddPossibleTarget(Entity *target) { possibleTargets.insert(target); }

  void RemovePossibleTarget(Entity *target) { possibleTargets.erase(target); }

  void Update(double deltaTime) override {
    UpdateFollowTarget(deltaTime);

    if (animationSystem->IsPerformingAnimation()) {
      animationSystem->Update(deltaTime);
      return;
    }

    UpdateVelocity(deltaTime);
    UpdateLastAnimationFromVelocity(deltaTime);
    position = Vector2Add(position, velocity);
    UpdateAnimationSystem(deltaTime);

    velocity = {0.0f, 0.0f};
  }

  void Draw() override {
    Entity::Draw();

#ifdef DEBUG
    DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y),
                    followRange, RED);
#endif
  }
};
