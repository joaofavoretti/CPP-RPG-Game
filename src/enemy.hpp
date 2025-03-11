#pragma once

#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <set>

#include "entity.hpp"

#define ENEMY_ANIMATION_BASE_PATH "../assets/pixel_art/3 Dungeon Enemies/1"

struct Enemy : Entity {

  float speed = 30.0f;
  Entity *target = nullptr;
  std::set<Entity *> possibleTargets;
  int attackDamage = 10;
  float attackRange = 40.0f;
  float followRange = 60.0f;
  float attackCooldown = 1.0f;
  float attackCooldownTimer = 0.0f;

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
    std::map<Entity::EntityAnimationId, Rectangle> animationBoundaryMap = {
        {Entity::EntityAnimationId::MOVE_RIGHT,
         Rectangle{
             .x = 0,
             .y = 12,
             .width =
                 static_cast<float>(animationSystem->GetSize().x * 2.1 / 3),
             .height =
                 static_cast<float>(animationSystem->GetSize().y * 1.1 / 4),
         }},
        {Entity::EntityAnimationId::MOVE_LEFT,
         Rectangle{
             .x = 9,
             .y = 12,
             .width =
                 static_cast<float>(animationSystem->GetSize().x * 2.1 / 3),
             .height =
                 static_cast<float>(animationSystem->GetSize().y * 1.1 / 4),
         }},
        {Entity::EntityAnimationId::MOVE_UP,
         Rectangle{
             .x = 10,
             .y = 7,
             .width =
                 static_cast<float>(animationSystem->GetSize().x * 1.1 / 3),
             .height = animationSystem->GetSize().y * 2 / 3,
         }},
        {Entity::EntityAnimationId::MOVE_DOWN,
         Rectangle{
             .x = 9,
             .y = 3,
             .width =
                 static_cast<float>(animationSystem->GetSize().x * 1.1 / 3),
             .height =
                 static_cast<float>(animationSystem->GetSize().y * 1.8 / 3),
         }},
    };

    Rectangle boundaries = animationBoundaryMap[lastMoveAnimation];

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
      if (Vector2Distance(target->GetBoundaryCenter(), GetBoundaryCenter()) >
          followRange) {
        target = nullptr;
      }
    }

    if (target == nullptr) {
      Entity *closestTarget = nullptr;
      float closestDistance = followRange;

      for (auto possibleTarget : possibleTargets) {
        float distance = Vector2Distance(possibleTarget->GetBoundaryCenter(),
                                         GetBoundaryCenter());
        if (distance < followRange && distance < closestDistance) {
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
    if (angle < 0)
      angle += 2 * PI;
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

    if (IsInAttackRange()) {
      if (attackCooldownTimer == 0.0f) {
        attackCooldownTimer = 0.0f;
        animationSystem->Update(attackAnimationsMap[lastMoveAnimation],
                                deltaTime);
      } else {
        animationSystem->Update(idleAnimationsMap[lastMoveAnimation],
                                deltaTime);
      }

      velocity = {0.0f, 0.0f};
      attackCooldownTimer = fmod(fmin(attackCooldownTimer + deltaTime, attackCooldown), attackCooldown);
      animationSystem->SetPosition(position);

      return;
    }

    if (Vector2Length(velocity) == 0) {
      animationSystem->Update(idleAnimationsMap[lastMoveAnimation], deltaTime);
    } else {
      animationSystem->Update(lastMoveAnimation, deltaTime);
    }

    animationSystem->SetPosition(position);
  }

  bool IsInAttackRange() {
    return target != nullptr &&
           Vector2Distance(target->GetBoundaryCenter(), GetBoundaryCenter()) <
               attackRange;
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
    UpdateAnimationSystem(deltaTime);

    position = Vector2Add(position, velocity);

    velocity = {0.0f, 0.0f};
  }

  void Draw() override {
    Entity::Draw();

#ifdef DEBUG
    Vector2 center = GetBoundaryCenter();
    DrawCircleLines(static_cast<int>(center.x), static_cast<int>(center.y),
                    followRange, RED);

    DrawCircleLines(static_cast<int>(center.x), static_cast<int>(center.y),
                    attackRange, BLUE);
#endif
  }
};
