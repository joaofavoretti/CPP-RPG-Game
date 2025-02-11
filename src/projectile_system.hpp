#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <algorithm>

#include "projectile.hpp"

struct ProjectileSystem {
	std::unique_ptr<Animation> baseAnimation;
	std::vector<std::unique_ptr<Projectile>> projectiles;

private:
	bool IsOutOfBounds(Projectile& projectile) {
		return projectile.GetPosition().x < 0 || projectile.GetPosition().x > GetScreenWidth() || projectile.GetPosition().y < 0 || projectile.GetPosition().y > GetScreenHeight();
	}

public:
	
	ProjectileSystem(std::unique_ptr<Animation> baseAnimation) : baseAnimation(std::move(baseAnimation)) {}

	void SetOffset(Vector2 offset) {
		baseAnimation->offset = offset;
	}

	void Add(ProjectileConfig projectileConfig) {
		std::unique_ptr<Animation> animation = std::make_unique<Animation>(*baseAnimation);
		animation->UpdateAngle(projectileConfig.angle);
		projectiles.push_back(std::make_unique<Projectile>(projectileConfig, std::move(animation)));
	}

	void Update(double deltaTime) {
		for (auto& projectile : projectiles) {
			projectile->Update(deltaTime);
		}

		projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [&](std::unique_ptr<Projectile>& projectile) {
			return IsOutOfBounds(*projectile);
		}), projectiles.end());
	}

	void Draw() {
		for (auto& projectile : projectiles) {
			projectile->Draw();
		}
	}
};

