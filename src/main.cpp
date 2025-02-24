#include <cfloat>
#include <memory>
#include <raylib.h>

#include "map.hpp"
#include "player.hpp"

#define RAYLIB_TMX_IMPLEMENTATION
#include "raylib-tmx.h"

#include "tmx.hpp"

std::unique_ptr<Player> player;
std::unique_ptr<TMX> tmx;

Vector2 pos = {0, 0};

void Setup() {
  player = std::make_unique<Player>((Vector2){10, 0});
  tmx = std::make_unique<TMX>("/archive/Tiled/first-map.tmx");
}

double t = 0.0f;

void Update(double deltaTime) {
  player->Update(deltaTime);

  // Move the map in a circle
  /*t += deltaTime;*/
  /*map->SetPosition(newPos);*/

  // Move the player
}

void Draw() {
  ClearBackground(RAYWHITE);

  tmx->Draw({0, 0}, WHITE);

  // Draw a small rectangle in the map, color RED if it collides with the map

  player->Draw();
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 480;

  InitWindow(screenWidth, screenHeight, "Sprite Testing Range");

  SetTargetFPS(60);

  Setup();

  while (!WindowShouldClose()) {
    double deltaTime = GetFrameTime();
    Update(deltaTime);

    BeginDrawing();
    Draw();
    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();
}
