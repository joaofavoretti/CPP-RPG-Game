#include <raylib.h>
#include <memory>
#include <cfloat>

#include "player.hpp"

std::unique_ptr<Player> player;

void Setup() {
	
	player = std::make_unique<Player>((Vector2){ 10, 0 });

}

void Update(double deltaTime) {
	player->Update(deltaTime);
}

void Draw() {
	ClearBackground(RAYWHITE);

	player->Draw();
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
