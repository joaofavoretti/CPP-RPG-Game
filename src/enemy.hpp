#pragma once

#include <raylib.h>
#include <raymath.h>
#include <memory>
#include <vector>
#include <map>
#include <random>

#include "sprite.hpp"

struct Enemy {
	Vector2 position;
	float baseSpeed = 1.0f;
	Vector2 velocity = { 0, 0 };
	double probabilityChangeDirection = 0.001;

	std::string TexturePath = "../assets/tiles.png";
	Texture2D texture;
	Rectangle textureTileRect;

	std::vector<std::unique_ptr<Sprite>> sprites;
	int spriteIndex = 0;
	float animationDuration = 0.2f;
	float animationCounter = 0.0f;

	enum class spriteType {
		POSITION_1,
		POSITION_2,
	};

	std::map<spriteType, Vector2> spritePosition = {
		{spriteType::POSITION_1, Vector2{4, 74}},
		{spriteType::POSITION_2, Vector2{5, 74}},
	};

private:
	Vector2 GetRandomVelocity() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(-1, 1);

		return { static_cast<float>(dis(gen)), static_cast<float>(dis(gen)) };
	}

	void UpdateVelocity(double deltaTime) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0, 1);

		if (dis(gen) < probabilityChangeDirection) {
			velocity = GetRandomVelocity();
		}	
	}

	bool isOutOfTheScreen(Vector2 position) {
		return position.x < 0 || position.y < 0 || position.x > GetScreenWidth() || position.y > GetScreenHeight();
	}

	void UpdatePosition(double deltaTime) {
		velocity = Vector2Normalize(velocity);
		velocity = Vector2Scale(velocity, baseSpeed * deltaTime);

		position = Vector2Add(position, velocity);

		Vector2 screenPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };
		if (screenPosition.x < 0 || screenPosition.x > GetScreenWidth()) {
			velocity.x *= -1;
		}
		if (screenPosition.y < 0 || screenPosition.y > GetScreenHeight()) {
			velocity.y *= -1;
		}
	}

	void UpdateSprite(double deltaTime) {
		animationCounter += deltaTime;
		if (animationCounter >= animationDuration) {
			animationCounter = 0.0f;
			spriteIndex = (spriteIndex + 1) % sprites.size();
		}
	}

public:
	Enemy(Vector2 position) : position(position) {
		texture = LoadTexture(TexturePath.c_str());
		textureTileRect = { 0, 0, 32, 32 };

		velocity = GetRandomVelocity();

		for (auto& [key, value] : spritePosition) {
			Vector2 screenPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };
			Vector2 tilePosition = value;
			sprites.push_back(std::make_unique<Sprite>(screenPosition, tilePosition, texture, textureTileRect));
		}
	}


	void update(double deltaTime) {
		UpdateVelocity(deltaTime);
		UpdatePosition(deltaTime);
		UpdateSprite(deltaTime);
	}

	void draw() {
		sprites[spriteIndex]->screenPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };
		sprites[spriteIndex]->Draw();
	}
};

