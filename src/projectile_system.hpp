#pragma once

#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "projectile.hpp"

struct ProjectileSystem {
	std::unique_ptr<Animation> baseAnimation;
	std::vector<std::unique_ptr<Projectile>> projectiles;

private:
	bool IsOutOfBounds(Projectile& projectile);

public:
	
	ProjectileSystem(std::unique_ptr<Animation> baseAnimation);

	void SetOffset(Vector2 offset);

	void Add(ProjectileConfig projectileConfig);

	void Update(double deltaTime);

	void Draw();
};

