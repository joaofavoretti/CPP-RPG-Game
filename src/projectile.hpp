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

	Projectile(ProjectileConfig config, std::unique_ptr<Animation> animation) : position(config.position), angle(config.angle), speed(config.speed), animation(std::move(animation)) {}

	void Update(double deltaTime) {
		Vector2 direction = Vector2{ cosf(angle), sinf(angle) };
		Vector2 velocity = Vector2Scale(direction, speed * deltaTime);
		position = Vector2Add(position, velocity);

		animation->Update(deltaTime);
		animation->UpdateScreenPosition(position);
	}

	Vector2 GetPosition() {
		return Vector2{ position.x + animation->offset.x, position.y + animation->offset.y };
	}

	void Draw() {
		animation->Draw();
	}
};
