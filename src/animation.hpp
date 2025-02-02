#pragma once

#include <raylib.h>
#include <string>

struct AnimationConfig {
	std::string texturePath;
	Vector2 textureTileSize;
	Vector2 texturePosition;
	int numberOfFrames;
	float frameSpeed;
	float scale;
	bool loop = false;
};

struct Animation {
	Texture2D texture;
	Vector2 textureTileSize;
	Vector2 texturePosition;
	float frameCounter = 0.0f;
	int numberOfFrames;
	int currentFrame = 0;
	float frameSpeed;
	bool loop;
	float scale;
	Vector2 screenPosition;

	Animation(AnimationConfig config, Vector2 screenPosition): screenPosition(screenPosition) {
		texture = LoadTexture(config.texturePath.c_str());
		textureTileSize = config.textureTileSize;
		texturePosition = config.texturePosition;
		numberOfFrames = config.numberOfFrames;
		frameSpeed = config.frameSpeed;
		scale = config.scale;
		loop = config.loop;
	}

	void UpdateScreenPosition(Vector2 screenPosition) {
		this->screenPosition = screenPosition;
	}

	void Reset() {
		currentFrame = 0;
	}

	void Update(double deltaTime) {
		frameCounter += deltaTime;
		if (frameCounter >= frameSpeed) {
			frameCounter = 0.0f;
			currentFrame = loop ? (currentFrame + 1) % numberOfFrames : std::min(currentFrame + 1, numberOfFrames - 1);
		}
	}

	void Draw() {
		
		Rectangle sourceRect = { (texturePosition.x + currentFrame) * textureTileSize.x, texturePosition.y * textureTileSize.y, textureTileSize.x, textureTileSize.y };
		Rectangle destRect = { screenPosition.x, screenPosition.y, textureTileSize.x * scale, textureTileSize.y  * scale};
		Vector2 origin = { 0.0f, 0.0f };
		
		DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
	}
};
