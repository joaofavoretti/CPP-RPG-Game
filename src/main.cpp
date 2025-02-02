#include <raylib.h>
#include <memory>
#include <cfloat>

#include "player.hpp"
#include "enemy.hpp"
#include "map.hpp"

#include "animation.hpp"

std::unique_ptr<Map> map;
std::unique_ptr<Player> player;
std::unique_ptr<Enemy> enemy;

std::unique_ptr<Animation> playerMoveRightAnimation;
std::unique_ptr<Animation> playerIdleAnimation;
bool isMovingRight = false;
Vector2 position = { 0, 64 };
int speed = 2;

void Setup() {
	/*map = std::make_unique<Map>();*/

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

	/*player = std::make_unique<Player>(Vector2{ 10, 10 });*/
	/*enemy = std::make_unique<Enemy>(Vector2{ 5, 5 });*/
	/**/
	/*player->RegisterEnemy(enemy.get());*/
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

	/*player->update(deltaTime);*/
	/*enemy->update(deltaTime);*/
}

void Draw() {
	ClearBackground(RAYWHITE);

	/*map->draw();*/
	if (IsKeyDown(KEY_RIGHT)) {
		playerMoveRightAnimation->Draw();
	}
	else {
		playerIdleAnimation->Draw();
	}
	/*player->draw();*/
	/*enemy->draw();*/
}


int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "TDB");

	SetTargetFPS(60);

	Setup();

	// Main game loop
	while (!WindowShouldClose()) {
		double deltaTime = GetFrameTime();
		Update(deltaTime);

		BeginDrawing();
		Draw();
		EndDrawing();
	}

	// De-Initialization
	CloseWindow();
}
