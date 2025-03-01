#include "projectile.hpp"

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

Rectangle Projectile::GetBoundaries() {
  return Rectangle{
      .x = position.x + boundaryConfig.x,
      .y = position.y + boundaryConfig.y,
      .width = boundaryConfig.width,
      .height = boundaryConfig.height,
  };
}

void Projectile::Draw() {
#ifdef DEBUG
  DrawRectangleLines(GetBoundaries().x, GetBoundaries().y,
                     GetBoundaries().width, GetBoundaries().height, RED);
#endif

  animation->Draw();
}
