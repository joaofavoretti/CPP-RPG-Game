#pragma once

#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>
#include <memory>

#include "sprite.hpp"

struct AnimatedSprite {
	Vector2 position;
	Vector2 velocity;

	int spriteIndex = 0;
	double animationLength = 0.1f;
	double animationCounter = 0.0f;
	
	Texture2D texture;
	Rectangle textureTileRect;

	std::vector<std::unique_ptr<Sprite>> sprites;

	AnimatedSprite(Vector2 position, Vector2 velocity, std::vector<Vector2>spritePositions, Texture2D texture, Rectangle textureTileRect) : position(position), velocity(velocity), texture(texture), textureTileRect(textureTileRect) {
		// Iterate through the spritePositions
		for (auto& spritePosition : spritePositions) {
			Vector2 screenPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };
			sprites.push_back(std::make_unique<Sprite>(screenPosition, spritePosition, texture, textureTileRect));
		}
	}

	void update(double deltaTime) {
		// Update Sprite indexing
		animationCounter += deltaTime;
		if (animationCounter >= animationLength) {
			animationCounter = 0.0f;
			spriteIndex = (spriteIndex + 1) % sprites.size();
		}

		// Update the position

		position = Vector2Add(position, velocity * deltaTime);
	}

	void draw() {
		sprites[spriteIndex]->screenPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };
		sprites[spriteIndex]->Draw();
	}
};
