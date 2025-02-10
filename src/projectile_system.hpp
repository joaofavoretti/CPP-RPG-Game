#pragma once

#include <raylib.h>
#include <raymath.h>
#include <memory>
#include <vector>

#include "projectile.hpp"
#include "animation.hpp"

struct ProjectileSystem {
	std::unique_ptr<Animation> baseAnimation;
	std::vector<Projectile> projectiles;

private:
	bool IsOutOfBounds(Projectile projectile) {
		return projectile.position.x < 0 || projectile.position.x > GetScreenWidth() || projectile.position.y < 0 || projectile.position.y > GetScreenHeight();
	}

public:
	ProjectileSystem(std::unique_ptr<Animation> baseAnimation) : baseAnimation(std::move(baseAnimation)) {}


	void Add(Projectile projectile) {
		projectiles.push_back(projectile);
	}

	void Update(double deltaTime) {
		// Update projectile positions
		for (auto& projectile : projectiles) {
			projectile.position = Vector2Add(projectile.position, Vector2Scale(Vector2{ cosf(projectile.angle), sinf(projectile.angle) }, projectile.speed));
		}

		// Remove out of bounds projectiles
		projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [&](Projectile projectile) {
			return IsOutOfBounds(projectile);
		}), projectiles.end());
	}

	void Draw() {
	}
};

