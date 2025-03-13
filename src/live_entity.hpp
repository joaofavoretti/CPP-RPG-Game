#pragma once

#include <raylib.h>
#include <raymath.h>

#include "entity.hpp"

struct LiveEntity : Entity {

  int maxHealth;
  int health;
  int enemyHealthBarWidth;

  std::vector<std::function<bool(Rectangle)>> collisionChecks;

public:
  LiveEntity(Vector2 position, Vector2 velocity, float scale, int health)
      : Entity(position, velocity, scale), maxHealth(health), health(health), enemyHealthBarWidth(20 * scale){
  }

  void TakeDamage(int damage) {
    health -= damage;
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

    DrawRectangle(boundaryCenter.x - enemyHealthBarWidth / 2, boundary.y - 5, enemyHealthBarWidth * health / maxHealth, 1, BLACK);
    DrawRectangle(boundaryCenter.x - enemyHealthBarWidth / 2, boundary.y - 5, enemyHealthBarWidth, 1, RED);
  }
 
  void Draw() override {
    Entity::Draw();
    DrawLifeBar();
  }
};

