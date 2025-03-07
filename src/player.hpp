#pragma once

#include <functional>
#include <map>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "entity.hpp"
#include "projectile_system.hpp"

#define PLAYER_SCALE 1.0f
#define PLAYER_BASE_SPEED 60.0f


struct Player : Entity {
private:
  float speed = PLAYER_BASE_SPEED * PLAYER_SCALE;
  int score;

  Entity::EntityAnimationId lastMoveAnimation = Entity::EntityAnimationId::MOVE_RIGHT;

  std::unique_ptr<ProjectileSystem> projectileSystem;

  std::vector<std::function<bool(Rectangle)>> collisionChecks;

  std::map<Entity::EntityAnimationId, Entity::EntityAnimationId> idleAnimations = {
    {Entity::EntityAnimationId::MOVE_RIGHT, Entity::EntityAnimationId::IDLE_RIGHT},
    {Entity::EntityAnimationId::MOVE_LEFT, Entity::EntityAnimationId::IDLE_LEFT},
    {Entity::EntityAnimationId::MOVE_UP, Entity::EntityAnimationId::IDLE_UP},
    {Entity::EntityAnimationId::MOVE_DOWN, Entity::EntityAnimationId::IDLE_DOWN}};

  std::map<Entity::EntityAnimationId, Entity::EntityAnimationId> attackAnimations = {
    {Entity::EntityAnimationId::MOVE_RIGHT, Entity::EntityAnimationId::ATTACK_RIGHT},
    {Entity::EntityAnimationId::MOVE_LEFT, Entity::EntityAnimationId::ATTACK_LEFT},
    {Entity::EntityAnimationId::MOVE_UP, Entity::EntityAnimationId::ATTACK_UP},
    {Entity::EntityAnimationId::MOVE_DOWN, Entity::EntityAnimationId::ATTACK_DOWN}};

  void RegisterAnimations() override;
  void SetupProjectileSystem();
  void UpdateProjectileSystem(double deltaTime);
  void UpdateAnimationSystem(double deltaTime);
  Rectangle GetBoundariesFromPosition(Vector2 position);
  bool IsAvailableToMove(Rectangle newBoundary);


public:
  Player(Vector2 position);
  Vector2 GetBoundaryCenter();
  Rectangle GetBoundaries() override;
  void AddCollisionCheck(std::function<bool(Rectangle)> collisionCheck);
  void AddScore(int amount) { score += amount; }
  Entity::EntityAnimationId GetLastMoveAnimation();
  void Update(double deltaTime) override;
  void Draw() override;
};
