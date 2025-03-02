#pragma once

#include <functional>
#include <map>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "animation.hpp"
#include "animation_system.hpp"

#define ENEMY_SCALE 1.0f
#define ENEMY_BASE_SPEED 60.0f

enum EnemyAnimationEnum {
  ENEMY_MOVE_RIGHT = 0,
  ENEMY_MOVE_LEFT,
  ENEMY_MOVE_UP,
  ENEMY_MOVE_DOWN,
  ENEMY_IDLE_RIGHT,
  ENEMY_IDLE_LEFT,
  ENEMY_IDLE_UP,
  ENEMY_IDLE_DOWN,
  ENEMY_ATTACK_RIGHT,
  ENEMY_ATTACK_LEFT,
  ENEMY_ATTACK_UP,
  ENEMY_ATTACK_DOWN,
};

static std::map<EnemyAnimationEnum, EnemyAnimationEnum> EnemyIdleAnimations = {
    {EnemyAnimationEnum::ENEMY_MOVE_RIGHT, EnemyAnimationEnum::ENEMY_IDLE_RIGHT},
    {EnemyAnimationEnum::ENEMY_MOVE_LEFT, EnemyAnimationEnum::ENEMY_IDLE_LEFT},
    {EnemyAnimationEnum::ENEMY_MOVE_UP, EnemyAnimationEnum::ENEMY_IDLE_UP},
    {EnemyAnimationEnum::ENEMY_MOVE_DOWN, EnemyAnimationEnum::ENEMY_IDLE_DOWN}};

static std::map<EnemyAnimationEnum, EnemyAnimationEnum> EnemyAttackAnimations = {
    {EnemyAnimationEnum::ENEMY_MOVE_RIGHT, EnemyAnimationEnum::ENEMY_ATTACK_RIGHT},
    {EnemyAnimationEnum::ENEMY_MOVE_LEFT, EnemyAnimationEnum::ENEMY_ATTACK_LEFT},
    {EnemyAnimationEnum::ENEMY_MOVE_UP, EnemyAnimationEnum::ENEMY_ATTACK_UP},
    {EnemyAnimationEnum::ENEMY_MOVE_DOWN, EnemyAnimationEnum::ENEMY_ATTACK_DOWN}};

struct Enemy {
private:
  Vector2 position;
  Vector2 velocity;
  float speed = ENEMY_BASE_SPEED * ENEMY_SCALE;

  std::unique_ptr<std::map<int, std::unique_ptr<Animation>>> animations;
  std::unique_ptr<AnimationSystem> animationSystem;
  EnemyAnimationEnum lastMoveAnimation = EnemyAnimationEnum::ENEMY_MOVE_RIGHT;

  std::vector<std::function<bool(Rectangle)>> collisionChecks;

  void SetupAnimations();
  void UpdateAnimationSystem(double deltaTime);
  Rectangle GetBoundariesFromPosition(Vector2 position);
  bool IsAvailableToMove(Rectangle newBoundary);

public:
  Enemy(Vector2 position);
  Vector2 GetPosition();
  Rectangle GetBoundaries();
  void AddCollisionCheck(std::function<bool(Rectangle)> collisionCheck);
  EnemyAnimationEnum GetLastMoveAnimation();
  void Update(double deltaTime);
  void Draw();
};
