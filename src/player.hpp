#pragma once

#include <raylib.h>
#include <raymath.h>
#include <string>
#include <map>
#include <vector>
#include <memory>

#include "sprite.hpp"

struct Player {
	Vector2 position;
	float speed = 5.0f;

	bool invertSprite = false;
	int spriteIndex = 0;
	double spriteIndexLength = 0.1f;
	double spriteIndexCounter = 0.0f;
	
	std::string TexturePath = "../assets/tiles.png";
	Texture2D texture;
	Rectangle textureTileRect;

	std::vector<std::unique_ptr<Sprite>> sprites;

	enum class spriteType {
		POSITION_1,
		POSITION_2,
	};

	std::map<spriteType, Vector2> spritePosition = {
		{spriteType::POSITION_1, Vector2{4, 74}},
		{spriteType::POSITION_2, Vector2{5, 74}},
	};

	Player(Vector2 position) : position(position) {
		texture = LoadTexture(TexturePath.c_str());
		textureTileRect = { 0, 0, 32, 32 };

		// Iterate through the spritePosition map
		for (auto& [key, value] : spritePosition) {
			Vector2 screenPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };
			Vector2 tilePosition = value;
			sprites.push_back(std::make_unique<Sprite>(screenPosition, tilePosition, texture, textureTileRect));
		}

	}

	void _updatePosition(double deltaTime) {
		Vector2 velocity = { 0, 0 };
		if (IsKeyDown(KEY_RIGHT)) {
			velocity.x += 1;

		}
		if (IsKeyDown(KEY_LEFT)) {
			velocity.x -= 1;
		}
		if (IsKeyDown(KEY_UP)) {
			velocity.y -= 1;
		}
		if (IsKeyDown(KEY_DOWN)) {
			velocity.y += 1;
		}

		// Update the player position
		velocity = Vector2Normalize(velocity);
		velocity = Vector2Scale(velocity, speed * deltaTime);

		position = Vector2Add(position, velocity);
	}

	void _updateSprite(double deltaTime) {
		bool isMoving = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN);

		if (!isMoving) {
			spriteIndex = 0;
			spriteIndexCounter = 0.0f;
			return;
		}

		spriteIndexCounter += deltaTime;
		if (spriteIndexCounter >= spriteIndexLength) {
			spriteIndexCounter = 0.0f;
			spriteIndex = (spriteIndex + 1) % sprites.size();
		}

		invertSprite = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_DOWN);
	}

	void update(double deltaTime) {
		_updatePosition(deltaTime);
		_updateSprite(deltaTime);
	}

	void draw() {
		// Draw the player
		sprites[spriteIndex]->screenPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };

		if (invertSprite)
			sprites[spriteIndex]->DrawMirrored();
		else 
			sprites[spriteIndex]->Draw();
	}
		
};
