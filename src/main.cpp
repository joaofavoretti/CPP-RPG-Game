#include <raylib.h>
#include <memory>
#include <cfloat>

#include "animation.hpp"
#include "animation_system.hpp"

std::unique_ptr<Animation> playerMoveRightAnimation;
std::unique_ptr<Animation> playerIdleAnimation;
std::unique_ptr<AnimationSystem> animationSystem;
Vector2 position = { 0, 64 };
int speed = 2;

enum PlayerAnimationEnum {
	MOVE_RIGHT = 0,
	IDLE
};

void SetupAnimations() {
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

void Setup() {
	SetupAnimations();

	animationSystem = std::make_unique<AnimationSystem>();
	animationSystem->RegisterAnimation(PlayerAnimationEnum::MOVE_RIGHT, playerMoveRightAnimation.get());
	animationSystem->RegisterAnimation(PlayerAnimationEnum::IDLE, playerIdleAnimation.get());
}

void Update(double deltaTime) {
	if (IsKeyDown(KEY_RIGHT)) {
		// Update player position
		position.x += speed;

		animationSystem->Update(PlayerAnimationEnum::MOVE_RIGHT, deltaTime);
	}
	else {
		animationSystem->Update(PlayerAnimationEnum::IDLE, deltaTime);
	}
	animationSystem->SetPosition(position);
}

void Draw() {
	ClearBackground(RAYWHITE);

	animationSystem->Draw();
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
