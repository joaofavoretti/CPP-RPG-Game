#pragma once

#include <raylib.h>
#include <raymath.h>
#include <functional>
#include <vector>

#include "projectile.hpp"

struct ProjectileSystem {
private:
  std::unique_ptr<Animation> baseAnimation;
  std::vector<std::unique_ptr<Projectile>> projectiles;
  std::vector<std::function<bool(Rectangle)>> collisionChecks;
  Rectangle boundaryConfig;

  bool IsOutOfBounds(Projectile &projectile);

public:
  ProjectileSystem(std::unique_ptr<Animation> baseAnimation, Rectangle boundaryConfig);
  void SetOffset(Vector2 offset);
  void Add(ProjectileConfig projectileConfig);
  void AddCollisionCheck(std::function<bool(Rectangle)> collisionCheck);
  void Update(double deltaTime);
  void Draw();
};
