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
	bool flip = false;
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
	bool flip;
	float scale;
	Vector2 screenPosition;

	Animation(AnimationConfig config, Vector2 screenPosition);

	void UpdateScreenPosition(Vector2 screenPosition);

	void Reset();

	void Update(double deltaTime);

	void Draw();
};
