#pragma once

#include <memory>
#include <raylib.h>
#include <raymath.h>

#include "animation.hpp"

struct ProjectileConfig {
  Vector2 position;
  float angle;
  float speed;
};

struct Projectile {
private:
  Vector2 position;
  float angle;
  float speed;
  Rectangle boundaryConfig;
  std::unique_ptr<Animation> animation;

public:
  Projectile(ProjectileConfig config, std::unique_ptr<Animation> animation,
             Rectangle boundaryConfig);
  Rectangle GetBoundaries();
  Vector2 GetPosition();
  void Update(double deltaTime);
  void Draw();
};
