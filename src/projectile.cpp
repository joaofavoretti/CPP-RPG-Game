#include "projectile.hpp"

#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <raymath.h>
#include <vector>

Projectile::Projectile(ProjectileConfig config,
                       std::unique_ptr<Animation> animation,
                       Rectangle boundaryConfig)
    : position(config.position), angle(config.angle), speed(config.speed),
      animation(std::move(animation)), boundaryConfig(boundaryConfig) {}

void Projectile::Update(double deltaTime) {
  Vector2 direction = Vector2{cosf(angle), sinf(angle)};
  Vector2 velocity = Vector2Scale(direction, speed * deltaTime);
  position = Vector2Add(position, velocity);

  animation->Update(deltaTime);
  animation->UpdateScreenPosition(position);
}

Vector2 Projectile::GetPosition() {
  return Vector2{position.x + animation->offset.x,
                 position.y + animation->offset.y};
}

Vector2 RotatePointAroundPivot(Vector2 point, Vector2 pivot, float angle) {
  float s = sinf(angle);
  float c = cosf(angle);

  point.x -= pivot.x;
  point.y -= pivot.y;

  float xnew = point.x * c - point.y * s;
  float ynew = point.x * s + point.y * c;

  point.x = xnew + pivot.x;
  point.y = ynew + pivot.y;

  return point;
}

Rectangle Projectile::GetBoundaries() {
  Rectangle initialBoundaries = {
      .x = position.x + boundaryConfig.x + animation->offset.x,
      .y = position.y + boundaryConfig.y + animation->offset.y,
      .width = boundaryConfig.width,
      .height = boundaryConfig.height,
  };

  Vector2 topLeft = {initialBoundaries.x, initialBoundaries.y};
  Vector2 topRight = {initialBoundaries.x + initialBoundaries.width,
                      initialBoundaries.y};
  Vector2 bottomLeft = {initialBoundaries.x,
                        initialBoundaries.y + initialBoundaries.height};
  Vector2 bottomRight = {initialBoundaries.x + initialBoundaries.width,
                         initialBoundaries.y + initialBoundaries.height};

  topLeft = RotatePointAroundPivot(topLeft, topLeft, angle);
  topRight = RotatePointAroundPivot(topRight, topLeft, angle);
  bottomLeft = RotatePointAroundPivot(bottomLeft, topLeft, angle);
  bottomRight = RotatePointAroundPivot(bottomRight, topLeft, angle);

  float minX = std::min({topLeft.x, topRight.x, bottomLeft.x, bottomRight.x});
  float minY = std::min({topLeft.y, topRight.y, bottomLeft.y, bottomRight.y});
  float maxX = std::max({topLeft.x, topRight.x, bottomLeft.x, bottomRight.x});
  float maxY = std::max({topLeft.y, topRight.y, bottomLeft.y, bottomRight.y});

  return Rectangle{
      .x = minX,
      .y = minY,
      .width = maxX - minX,
      .height = maxY - minY,
  };
}

void Projectile::Draw() {
#ifdef DEBUG
  DrawRectangleLines(GetBoundaries().x, GetBoundaries().y,
                     GetBoundaries().width, GetBoundaries().height, RED);
#endif

  animation->Draw();
}
