#pragma once

#include <map>
#include <memory>
#include <raylib.h>
#include <raymath.h>

#include "animation.hpp"
#include "animation_system.hpp"
#include "projectile_system.hpp"

#define PLAYER_SCALE 1.0f
#define PLAYER_BASE_SPEED 60.0f

// Has to start with 0
enum PlayerAnimationEnum {
  MOVE_RIGHT = 0,
  MOVE_LEFT,
  MOVE_UP,
  MOVE_DOWN,
  IDLE_RIGHT,
  IDLE_LEFT,
  IDLE_UP,
  IDLE_DOWN,
  ATTACK_RIGHT,
  ATTACK_LEFT,
  ATTACK_UP,
  ATTACK_DOWN,
};

static std::map<PlayerAnimationEnum, PlayerAnimationEnum> idleAnimations = {
    {PlayerAnimationEnum::MOVE_RIGHT, PlayerAnimationEnum::IDLE_RIGHT},
    {PlayerAnimationEnum::MOVE_LEFT, PlayerAnimationEnum::IDLE_LEFT},
    {PlayerAnimationEnum::MOVE_UP, PlayerAnimationEnum::IDLE_UP},
    {PlayerAnimationEnum::MOVE_DOWN, PlayerAnimationEnum::IDLE_DOWN}};

static std::map<PlayerAnimationEnum, PlayerAnimationEnum> attackAnimations = {
    {PlayerAnimationEnum::MOVE_RIGHT, PlayerAnimationEnum::ATTACK_RIGHT},
    {PlayerAnimationEnum::MOVE_LEFT, PlayerAnimationEnum::ATTACK_LEFT},
    {PlayerAnimationEnum::MOVE_UP, PlayerAnimationEnum::ATTACK_UP},
    {PlayerAnimationEnum::MOVE_DOWN, PlayerAnimationEnum::ATTACK_DOWN}};

struct Player {
private:
  Vector2 position;
  Vector2 velocity;
  float speed = PLAYER_BASE_SPEED * PLAYER_SCALE;

  std::unique_ptr<std::map<int, std::unique_ptr<Animation>>> animations;
  std::unique_ptr<AnimationSystem> animationSystem;
  PlayerAnimationEnum lastMoveAnimation = PlayerAnimationEnum::MOVE_RIGHT;

  std::unique_ptr<ProjectileSystem> projectileSystem;

  void SetupAnimations();
  void SetupProjectileSystem();
  void UpdateProjectileSystem(double deltaTime);
  void UpdateAnimationSystem(double deltaTime);

public:
  Player(Vector2 position);
  Vector2 GetPosition();
  Rectangle GetBoundaries();
  PlayerAnimationEnum GetLastMoveAnimation();
  void Update(double deltaTime);
  void Draw();
};
