// #include <iostream>
#include <raylib.h>
#include <memory>
#include <cfloat>

#include "player.hpp"
#include "map.hpp"

std::unique_ptr<Map> map;
std::unique_ptr<Player> player;

void setup() {
	map = std::make_unique<Map>();
	player = std::make_unique<Player>(Vector2{ 10, 10 });
}

void update(double deltaTime) {
	player->update(deltaTime);
}

void draw() {
	ClearBackground(RAYWHITE);

	map->draw();
	player->draw();
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
