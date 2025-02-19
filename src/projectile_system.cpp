#include <algorithm>

#include "projectile_system.hpp"

bool ProjectileSystem::IsOutOfBounds(Projectile &projectile) {
  return projectile.GetPosition().x < 0 ||
         projectile.GetPosition().x > GetScreenWidth() ||
         projectile.GetPosition().y < 0 ||
         projectile.GetPosition().y > GetScreenHeight();
}

ProjectileSystem::ProjectileSystem(std::unique_ptr<Animation> baseAnimation)
    : baseAnimation(std::move(baseAnimation)) {}

void ProjectileSystem::SetOffset(Vector2 offset) {
  baseAnimation->offset = offset;
}

void ProjectileSystem::Add(ProjectileConfig projectileConfig) {
  std::unique_ptr<Animation> animation =
      std::make_unique<Animation>(*baseAnimation);
  animation->UpdateAngle(projectileConfig.angle);
  projectiles.push_back(
      std::make_unique<Projectile>(projectileConfig, std::move(animation)));
}

void ProjectileSystem::Update(double deltaTime) {
  for (auto &projectile : projectiles) {
    projectile->Update(deltaTime);
  }

  projectiles.erase(
      std::remove_if(projectiles.begin(), projectiles.end(),
                     [&](std::unique_ptr<Projectile> &projectile) {
                       return IsOutOfBounds(*projectile);
                     }),
      projectiles.end());
}

void ProjectileSystem::Draw() {
  for (auto &projectile : projectiles) {
    projectile->Draw();
  }
}
