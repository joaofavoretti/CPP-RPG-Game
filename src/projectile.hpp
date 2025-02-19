#pragma once

#include <raylib.h>
#include <raymath.h>
#include <memory>

#include "animation.hpp"

struct ProjectileConfig {
	Vector2 position;
	float angle;
	float speed;
};

struct Projectile {
	Vector2 position;
	float angle;
	float speed;
	std::unique_ptr<Animation> animation;

	Projectile(ProjectileConfig config, std::unique_ptr<Animation> animation);

	void Update(double deltaTime);

	Vector2 GetPosition();

	void Draw();
};
