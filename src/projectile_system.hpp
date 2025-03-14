#pragma once

#include <functional>
#include <raylib.h>
#include <raymath.h>
#include <set>
#include <vector>

#include "live_entity.hpp"
#include "projectile.hpp"

struct ProjectileSystem {
private:
  std::unique_ptr<Animation> baseAnimation;
  std::vector<std::unique_ptr<Projectile>> projectiles;
  std::vector<std::function<bool(Rectangle)>> collisionChecks;
  std::set<LiveEntity *> possibleTargets;
  Rectangle boundaryConfig;

  bool IsOutOfBounds(Projectile &projectile);

public:
  ProjectileSystem(std::unique_ptr<Animation> baseAnimation,
                   Rectangle boundaryConfig);
  void SetOffset(Vector2 offset);
  void Add(ProjectileConfig projectileConfig);
  void AddCollisionCheck(std::function<bool(Rectangle)> collisionCheck);
  void AddPossibleTarget(LiveEntity *target) { possibleTargets.insert(target); }
  void RemovePossibleTarget(LiveEntity *target) {
    possibleTargets.erase(target);
  }
  void Update(double deltaTime);
  void Draw();
};
