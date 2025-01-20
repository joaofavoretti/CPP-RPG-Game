#include <iostream>
#include <raylib.h>

int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Simple Raylib Game");

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose()) {
	   // Update

	   // Draw
	   BeginDrawing();
	   ClearBackground(RAYWHITE);
	   DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
	   EndDrawing();
	}

	// De-Initialization
	CloseWindow();
}
