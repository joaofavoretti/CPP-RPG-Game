#include <raylib.h>
#include <memory>
#include <cfloat>

#include "player.hpp"
#include "enemy.hpp"
#include "map.hpp"

std::unique_ptr<Map> map;
std::unique_ptr<Player> player;
std::unique_ptr<Enemy> enemy;

void setup() {
	map = std::make_unique<Map>();
	player = std::make_unique<Player>(Vector2{ 10, 10 });
	enemy = std::make_unique<Enemy>(Vector2{ 5, 5 });

	player->RegisterEnemy(enemy.get());
}

void update(double deltaTime) {
	player->update(deltaTime);
	enemy->update(deltaTime);
}

void draw() {
	ClearBackground(RAYWHITE);

	map->draw();
	player->draw();
	enemy->draw();
}


int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "TDB");

	SetTargetFPS(60);

	setup();

	// Main game loop
	while (!WindowShouldClose()) {
		double deltaTime = GetFrameTime();
		update(deltaTime);

		BeginDrawing();
		draw();
		EndDrawing();
	}

	// De-Initialization
	CloseWindow();
}
