#include <raylib.h>
#include <memory>
#include <cfloat>

#include "animation.hpp"

std::unique_ptr<Animation> playerMoveRightAnimation;
std::unique_ptr<Animation> playerIdleAnimation;
bool isMovingRight = false;
Vector2 position = { 0, 64 };
int speed = 2;

void Setup() {
	AnimationConfig playerMoveRightConfig = {
		.texturePath = "../assets/pixel_art/1 Characters/1/D_Walk.png",
		.textureTileSize = { 32, 32 },
		.texturePosition = { 0, 0 },
		.numberOfFrames = 6,
		.frameSpeed = 0.1f,
		.scale = 2.0f,
		.loop = true
	};

	playerMoveRightAnimation = std::make_unique<Animation>(playerMoveRightConfig, position);


	AnimationConfig playerIdleConfig = {
		.texturePath = "../assets/pixel_art/1 Characters/1/D_Idle.png",
		.textureTileSize = { 32, 32 },
		.texturePosition = { 0, 0 },
		.numberOfFrames = 4,
		.frameSpeed = 0.1f,
		.scale = 2.0f,
		.loop = true
	};

	playerIdleAnimation = std::make_unique<Animation>(playerIdleConfig, position);
}

void Update(double deltaTime) {
	if (IsKeyDown(KEY_RIGHT)) {
		playerIdleAnimation->Reset();
		position.x += speed;
		playerMoveRightAnimation->UpdateScreenPosition(position);
		playerMoveRightAnimation->Update(deltaTime);
	}
	else {
		playerMoveRightAnimation->Reset();
		playerIdleAnimation->Update(deltaTime);
	}

	playerIdleAnimation->UpdateScreenPosition(position);
}

void Draw() {
	ClearBackground(RAYWHITE);

	if (IsKeyDown(KEY_RIGHT)) {
		playerMoveRightAnimation->Draw();
	}
	else {
		playerIdleAnimation->Draw();
	}
}


int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "TDB");

	SetTargetFPS(60);

	Setup();

	while (!WindowShouldClose()) {
		double deltaTime = GetFrameTime();
		Update(deltaTime);

		BeginDrawing();
		Draw();
		EndDrawing();
	}

	CloseWindow();
}
