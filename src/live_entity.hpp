#pragma once

#include <raylib.h>
#include <raymath.h>
#include <set>

#include "entity.hpp"

struct LiveEntity : Entity {

  int maxHealth;
  int health;
  int enemyHealthBarWidth;

  std::vector<std::function<bool(Rectangle)>> collisionChecks;
  std::set<LiveEntity *> possibleTargets;

public:
  LiveEntity(Vector2 position, Vector2 velocity, float scale, int health)
      : Entity(position, velocity, scale), maxHealth(health), health(health), enemyHealthBarWidth(20 * scale){
  }

  void TakeDamage(int damage) {
    health = fmax(health - damage, 0);
  }

  bool IsDead() {
    return health <= 0;
  }

  bool IsAlive() {
    return !IsDead();
  }

  virtual void AddPossibleTarget(LiveEntity *target) { possibleTargets.insert(target); }

  virtual void RemovePossibleTarget(LiveEntity *target) {
    possibleTargets.erase(target);
  }

  bool IsAvailableToMove(Rectangle newBoundary) {
    for (auto &collisionCheck : collisionChecks) {
      if (collisionCheck(newBoundary)) {
        return false;
      }
    }

    return true;
  }

  virtual void AddCollisionCheck(
    std::function<bool(Rectangle)> collisionCheck) {
    collisionChecks.push_back(collisionCheck);
  }

  void DrawLifeBar() {
    Rectangle boundary = GetBoundaries();
    Vector2 boundaryCenter = GetBoundaryCenter();

    DrawRectangle(boundaryCenter.x - enemyHealthBarWidth / 2, boundary.y - 5, enemyHealthBarWidth, 1, BLACK);
    DrawRectangle(boundaryCenter.x - enemyHealthBarWidth / 2, boundary.y - 5, enemyHealthBarWidth * health / maxHealth, 1, RED);
  }
 
  void Draw() override {
    Entity::Draw();
    DrawLifeBar();
  }
};

