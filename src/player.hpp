#pragma once

#include <raylib.h>
#include <raymath.h>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

#include "sprite.hpp"
#include "animated_sprite.hpp"

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

	std::unique_ptr<Sprite> wandSprite;
	std::vector<std::unique_ptr<AnimatedSprite>> shotSprites;

	enum class spriteType {
		POSITION_1,
		POSITION_2,
	};

	std::map<spriteType, Vector2> spritePosition = {
		{spriteType::POSITION_1, Vector2{4, 74}},
		{spriteType::POSITION_2, Vector2{5, 74}},
	};

	std::vector<Vector2> shotSpritePositions = {
		{41, 25},
		{42, 25},
		{43, 25},
		{44, 25},
		{45, 25},
		{46, 25},
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

		wandSprite = std::make_unique<Sprite>(Vector2{ 0, 0 }, Vector2{ 14, 44 }, texture, textureTileRect);

	}

	void _updatePosition(double deltaTime) {
		Vector2 velocity = { 0, 0 };
		if (IsKeyDown(KEY_D)) {
			velocity.x += 1;
		}
		if (IsKeyDown(KEY_A)) {
			velocity.x -= 1;
		}
		if (IsKeyDown(KEY_W)) {
			velocity.y -= 1;
		}
		if (IsKeyDown(KEY_S)) {
			velocity.y += 1;
		}

		// Update the player position
		velocity = Vector2Normalize(velocity);
		velocity = Vector2Scale(velocity, speed * deltaTime);

		position = Vector2Add(position, velocity);

		Vector2 screenPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };
		if (isOutOfTheScreen(screenPosition)) {
			position.x = position.x < 0 ? GetScreenWidth() / textureTileRect.width : 0;
			position.y = position.y < 0 ? GetScreenHeight() / textureTileRect.height : 0;
		}
	}

	void _updateSprite(double deltaTime) {
		bool isMoving = IsKeyDown(KEY_D) || IsKeyDown(KEY_A) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S);

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

		invertSprite = IsKeyDown(KEY_D) || IsKeyDown(KEY_S);
	}

	bool isOutOfTheScreen(Vector2 position) {
		return position.x < 0 || position.y < 0 || position.x > GetScreenWidth() || position.y > GetScreenHeight();
	}

	void _updateShots(double deltaTime) {
		for (auto& shotSprite : shotSprites) {
			shotSprite->update(deltaTime);
		}

		// Remove the shots that are out of the screen
		shotSprites.erase(std::remove_if(shotSprites.begin(), shotSprites.end(), [&](const std::unique_ptr<AnimatedSprite>& shotSprite) {
			Vector2 screenPosition = { shotSprite->position.x * textureTileRect.width, shotSprite->position.y * textureTileRect.height };
			return isOutOfTheScreen(screenPosition);
		}), shotSprites.end());

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePosition = GetMousePosition();
			Vector2 playerPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };
			Vector2 direction = { mousePosition.x - playerPosition.x, mousePosition.y - playerPosition.y };
			
			// Normalize the direction vector
			float speed = 500.0f * deltaTime;
			Vector2 velocity = Vector2Scale(Vector2Normalize(direction), speed);
			shotSprites.push_back(std::make_unique<AnimatedSprite>(position, velocity, shotSpritePositions, texture, textureTileRect));
		}
	}

	void update(double deltaTime) {
		_updatePosition(deltaTime);
		_updateSprite(deltaTime);
		_updateShots(deltaTime);
	}

	void draw() {
		// Drawing the player weapon
		wandSprite->screenPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };
		if (spriteIndex == 0) {
			if (invertSprite) {
				wandSprite->rotation = -45.0f;
				wandSprite->offset = { 10, 0 };
			} else {
				wandSprite->rotation = 45.0f;
				wandSprite->offset = { -10, 0 };
			}
		} else {
			wandSprite->offset = { 0, 0 };
			if (invertSprite) {
				wandSprite->rotation = 45.0f;
			} else {
				wandSprite->rotation = -45.0f;
			}
		}

		// Draw the shots
		for (auto& shotSprite : shotSprites) {
			shotSprite->draw();
		}

		// Draw the player
		sprites[spriteIndex]->screenPosition = { position.x * textureTileRect.width, position.y * textureTileRect.height };

		if (invertSprite) {
			wandSprite->Draw();
			sprites[spriteIndex]->DrawMirrored();
		} else {
			wandSprite->DrawMirrored();
			sprites[spriteIndex]->Draw();
		}
	}
		
};
